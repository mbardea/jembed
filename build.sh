set -e 

DIR=$PWD
cd java 
mvn package

cd $DIR
mkdir -p build
cd build
rm -f CMakeCache.txt
cmake ..
make 

cd $DIR

echo HOW TO RUN:
echo cd build
echo chost/chost

