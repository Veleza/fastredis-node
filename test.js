var fastredis = require('./build/Release/fastredis');

var r = fastredis('138.68.184.121');

r.select(2);

var start = process.hrtime();
var data = r.get('users.9a7fb83a-473b-481e-9403-6a9024cdcee4');
var end = process.hrtime(start);
console.log("Execution time (hr): ", end[0], end[1]/1000000);
console.log(data);

