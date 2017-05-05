# fastredis-node

Node extension that wraps [hiredis][hiredis].
Because Node is already good at doing I/O, fastredis-node only provides
bindings to the protocol parser.
It provides a fast sync GET operation. 

[hiredis]: http://github.com/redis/hiredis

## Install

Install with [NPM][npm]:

```
npm install fastredis
```

This requires:
* `gcc` / `g++` 4.8 or newer.
* `python` 2.7 or any newer 2.x version. `python` 3.x is not supported.

For running on Travis check the bundled [.travis.yml](.travis.yml).

[npm]: https://npmjs.org/

## Usage

fastredis-node works out of the box.

```javascript
var fastredis = require("fastredis");

var redis = fastredis();

// Select database 2
redis.select(2);

// Get some key
var data = redis.get('my_awesome_key');
```

## License

This code is released under the BSD license, after the license of hiredis.
