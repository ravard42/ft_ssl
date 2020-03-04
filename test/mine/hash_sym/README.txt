find $PATH -type f | xargs sh launch.sh

NB : it will test all the file recursively from source path $PATH on digest (md5, sha256) and sym cipher (all des and des3 with -a option)
