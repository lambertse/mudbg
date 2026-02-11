mkdir build
cd build

# Get the param for release or debug build 
if [ "$1" == "release" ]; then
  echo "Building in release mode"
  cmake .. -DCMAKE_BUILD_TYPE=release
elif [ "$1" == "clean" ]; then
  echo "Clean project"
  rm -rf *
else
  echo "Building in debug mode"
  cmake .. -DCMAKE_BUILD_TYPE=debug
fi

cmake --build .
