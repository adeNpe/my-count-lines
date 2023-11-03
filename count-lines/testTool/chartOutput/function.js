function giveValue() {
	document.getElementById('summary').innerHTML = "The total number of code lines: " + codeAll;
	document.getElementById('cID').innerHTML = "C/Cpp: " + c + " (" + cP + "%)";
	document.getElementById('javaID').innerHTML = "Java: " + java + " (" + javaP + "%)";
	document.getElementById('pythonID').innerHTML = "Python: " + python + " (" + pythonP + "%)";
	document.getElementById('htmlID').innerHTML = "HTML: " + html + " (" + htmlP + "%)";
	document.getElementById('unID').innerHTML = "unrecognized: " + unrecognized + " (" + unP + "%)";
	
	document.getElementById('cFunctionNum').innerHTML = "the number of function: " + cFunctionNum;
	document.getElementById('cFunctionCodeNum').innerHTML = "the number of function lines: " + cFunctionCodeNum;
	document.getElementById('cAverageFunctionCodeNum').innerHTML = "the average of function lines: " + cAverageFunctionCodeNum;
	document.getElementById('cSingleFunctionCodeNumMax').innerHTML = "the number of the longest function lines: " + cSingleFunctionCodeNumMax;
	document.getElementById('cSingleFunctionCodeNumMin').innerHTML = "the number of the shortest function lines: " + cSingleFunctionCodeNumMin;
	
	document.getElementById('javaFunctionNum').innerHTML = "the number of function: " + javaFunctionNum;
	document.getElementById('javaFunctionCodeNum').innerHTML = "the number of function lines: " + javaFunctionCodeNum;
	document.getElementById('javaAverageFunctionCodeNum').innerHTML = "the average of function lines: " + javaAverageFunctionCodeNum;
	document.getElementById('javaSingleFunctionCodeNumMax').innerHTML = "the number of the longest function lines: " + javaSingleFunctionCodeNumMax;
	document.getElementById('javaSingleFunctionCodeNumMin').innerHTML = "the number of the shortest function lines: " + javaSingleFunctionCodeNumMin;
}