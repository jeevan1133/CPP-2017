#/bin/bash

ask_user_input() {
   while read line
   do
      if [[ "$line" == "y" || "$line" == "Y" ]]; then
         break
      fi
   done < "${1:-/dev/stdin}"
}
