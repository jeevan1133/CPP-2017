#pragma once
#include <experimental/filesystem>
#include <chrono>
#include <thread>
#include <unordered_map>
#include <string>
#include <functional>

enum class FileStatus { created, modified, erased };
namespace fs = std::experimental::filesystem;

class FileWatcher {
   private:
      std::unordered_map<string, fs::file_time_type> paths_;
      bool running_ = true;
      bool contains(const std::string &key) {
         auto el = paths_.find(key);
         return el != paths_.end();
      }

   public:
      std::string path_to_watch;
      // Time interval at which we check the base folder for changes
      std::chrono::duration<int, milli> delay;

      // Keep a record of files from the base directory and 
      // their last modification time
      FileWatcher(std::string path_to_watch, 
            std::chrono::duration<int, milli> delay) : 
         path_to_watch{path_to_watch} , delay{delay} 
      {
         for (auto &file : fs::recursive_directory_iterator( path_to_watch)) {
            paths_[file.path().string()] = fs::last_write_time(file);
         }
      }

      // Monitor "path_to_watch" for changes and 
      // in case of a change execute the user supplied "action" function
      void start(const function<
            void (std::string, FileStatus)> 
            &action) 
      {
         while(running_) {
            // Wait for "delay" milliseconds
            std::this_thread::sleep_for(delay);
            auto it = paths_.begin();
            while (it != paths.end()) {
               if (!fs::exists(it->first)) {
                  action(it->first, FileStatus::erased);
                  it = paths_.erase(it);
               }
               else {
                  it++;
               }
            }
            // Check if a file was created or modified
            for (auto &file : fs::recursive_directory_iterator (path_to_watch)) {
               auto last_write_time = fs::last_write_time(file);
               // File creation
               if(!contains(file.path().string())) {
                  paths_[file.path().string()] = current_file_last_write_time;
                  action(file.path().string(), FileStatus::created);
               }
               // File modification
               else {
                  if(paths_[file.path().string()] != current_file_last_write_time) {
                     paths_[file.path().string()] = current_file_last_write_time;
                     action(file.path().string(), FileStatus::modified);
                  }
               }
            }

         }

      }
};
