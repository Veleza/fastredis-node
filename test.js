var fastredis = require('./build/Release/fastredis');

var r = fastredis();

r.select(2);

var start = process.hrtime();
var data = r.get('my_awesome_key');
var end = process.hrtime(start);
console.log("Execution time (hr): ", end[0], end[1]/1000000);
console.log(data);

