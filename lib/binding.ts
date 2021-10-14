const native = require('../build/Release/native.node')

export class RevPi {

	constructor(){

	}

	getDeviceList() : {
		name: string;
		address: number;
	}[] {
		return native.getDeviceList()
	}

	readValue(variableName: string) : number{
		return native.readValue(variableName)
	}

	writeValue(variableName: string, value: number){
		return native.writeValue(variableName, value);
	}
}
