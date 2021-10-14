#!/usr/bin/env node

import yargs from 'yargs';
import { hideBin } from 'yargs/helpers';
import { RevPi } from "./binding";

const parser = yargs(hideBin(process.argv))
	.options({
		r: {type: 'string'}, //Read
		w: {type: 'string'}, //Write
		v: {type: 'number'}, //Value
		d: {type: 'boolean'} //Devices
	})
  // Use the commands directory to scaffold.
  // Enable strict mode.
  .strict()
  // Useful aliases.
  .alias({ h: 'help' });

(async () => {
	const argv = await parser.argv

	const pi = new RevPi()

	if(argv.d && !argv.r && !argv.w){
		const devices = pi.getDeviceList()
		console.log("Devices", devices)

	}else if(argv.r && !argv.w && !argv.d){
		const val = pi.readValue(argv.r);
		console.log(`${argv.r}: ${val}`);
	}else if(argv.w && argv.v && !argv.d && !argv.r){
		pi.writeValue(argv.w, argv.v);
		console.log(`Wrote ${argv.w}: ${argv.v}`)
	}

})()