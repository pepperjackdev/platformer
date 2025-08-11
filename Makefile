
ifndef VERBOSE
.SILENT:
endif

# Runs the project
r: b
	./build/platformer

# Builds the sources with build-system
b: g
	ninja -C build

# Generates the build-system's scripts
g:
	cmake -B build -G Ninja