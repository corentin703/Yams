
function Component()
{
    // Contructor
}

Component.prototype.createOperations = function()
{
	component.createOperations();

	component.addElevatedOperation("Execute", "@TargetDir@/vc_redist.x64.exe", "/quiet", "/norestart");
	
	component.addOperation("Delete", "@TargetDir@/vc_redist.x64.exe");
}