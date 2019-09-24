 #!/bin/sh
export DYLD_LIBRARY_PATH=.
export DYLD_INSERT_LIBRARIES="libmalloc_x86_64_Darwin.so"
export DYLD_FORCE_FLAT_NAMESPACE=1
$@