all:
	node-gyp configure build

clean:
	node-gyp clean

temp:
	rm -rf tmp/fastredis
	mkdir -p tmp/fastredis
	cp -r README* COPYING *.js* binding.gyp src deps tmp/fastredis
	cd tmp/fastredis && rm -rf deps/*/.git* deps/*/*.o deps/*/*.a

package: temp
	cd tmp && tar -czvf fastredis.tgz fastredis

check:
	npm test
