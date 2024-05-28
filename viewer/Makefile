.PHONY: debug clean

debug:
	conan install conanfile.txt --build=missing -s build_type=Debug
	cmake --preset conan-debug
	cmake --build --preset conan-debug
	# Make ccls happy
	cp ./build/Debug/compile_commands.json ./

clean:
	rm -rf ./Debug
