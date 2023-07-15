const fs = require('fs');
const child_process =  require('child_process');
const path = require('path');
const { log } = require('console');

function requireGlobal(packageName) {
	var globalNodeModules = child_process.execSync('npm root -g').toString().trim();
	var packageDir = path.join(globalNodeModules, packageName);
	if (!fs.existsSync(packageDir))
		packageDir = path.join(globalNodeModules, 'npm/node_modules', packageName); //find package required by old npm
console.log(packageDir)
	if (!fs.existsSync(packageDir))
		throw new Error('Cannot find global module \'' + packageName + '\'');

	var packageMeta = JSON.parse(fs.readFileSync(path.join(packageDir, 'package.json')).toString());
	var main = path.join(packageDir, packageMeta.main);

	return require(main);
}

const csv = requireGlobal('csv');
console.log(csv)

function readCsv(fn) {
	return new Promise(r => {
		const p1 = csv.parse({ delimiter: ',', columns: true }, (_, result) => {
			//console.log(result);
			r(result);
		});

		fs.createReadStream(fn).pipe(p1);
	});
}

function mergeTo(rows, out) {
	for (const row of rows) {
		if (!row.MPN) {
			continue;
		}

		const found = out.find(r => r.MPN === row.MPN);
		if (!found) {
			out.push(row);
			continue;
		}

		found.Qty = (+found.Qty) + (+row.Qty);
	}
}

function multiply(rows, amount) {
	for (const row of rows) {
		if (!row.MPN) {
			continue;
		}

		row.Qty = (+row.Qty) * amount;
	}
}

function saveCSV(rows) {
	return new Promise(r => {
		csv.stringify(rows, {
			delimiter: ',',
			quote: true,
			header: true,
			columns: [{ key: 'MPN' }, { key: 'Qty' }]
		}, function (err, records) {
			r(records);
		});
	})
}

(async() => {
	const x1 = await readCsv('./Drivers/UCC21520DWR/UCC21520DWR.csv');
	const x2 = await readCsv('./MosfetBoard/IPB072N15N3G/IPB072N15N3G.csv');
	const x3 = await readCsv('./PowerBoard/LT8316/LT8316.csv');
	const out = [];
	multiply(x1, 3);
	mergeTo(x1, out);
	mergeTo(x2, out);
	mergeTo(x3, out);

	//console.log(out);
	const result = await saveCSV(out);
	log(result);
	fs.writeFileSync('out.csv', result);
})();
//{
// quote: true,
// 	objectMode: true,
// 	}