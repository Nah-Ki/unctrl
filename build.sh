

#!/bin/bash
set -e

echo "🛠 Rebuilding project..."

rm -rf build
mkdir build
cd build
cmake ..
make

echo "✅ Build complete."

echo "🚀 Running game..."
./unctrl


