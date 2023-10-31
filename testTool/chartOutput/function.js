function giveValue() {
	document.getElementById('summary').innerHTML = "The total number of code lines: " + codeAll;
	document.getElementById('cID').innerHTML = "C/Cpp: " + c + " (" + cP + "%)";
	document.getElementById('javaID').innerHTML = "Java: " + java + " (" + javaP + "%)";
	document.getElementById('pythonID').innerHTML = "Python: " + python + " (" + pythonP + "%)";
	document.getElementById('htmlID').innerHTML = "HTML: " + html + " (" + htmlP + "%)";
	document.getElementById('unID').innerHTML = "unrecognized: " + unrecognized + " (" + unP + "%)";
}