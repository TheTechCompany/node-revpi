const native = require('../build/Release/native.node')

export class RevPi {

	constructor(){

	}

	getDeviceList() : {
		name: string
	}[] {
		return native.getDeviceList()
	}

	readValue(variableName: string) : number{
		return native.readValue(variableName)
	}

	writeValue(){

	}
}
