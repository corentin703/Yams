
function Component()
{
    // Contructor
}

Component.prototype.createOperations = function()
{
	component.createOperations();

	if (systemInfo.productType === "windows") {
		component.addOperation("CreateShortcut", "@TargetDir@/Yams.exe", "@StartMenuDir@/Yams.lnk",
			"workingDirectory=@TargetDir@", "description=Lancer le Yams");
	}
}