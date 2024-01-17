#/bin/bash

# bash delimit.sh words.txt

sed -e '1 i\R"(' -e '$a)"' "$1" > "$1.raw" # Prepend R"#(  Append )#"
