.PHONY: debug clean

debug:
	cmake -B ./Debug -DCMAKE_BUILD_TYPE=Debug
	cmake --build ./Debug
	# Make ccls happy
	cp ./Debug/compile_commands.json ./

clean:
	rm -rf ./Debug
