
function Component()
{
    // Contructor
}

Component.prototype.createOperations = function()
{
	component.createOperations();

	// Le retour 3010 signifie qu'il y a peut-être besoin d'un redémarrage mais c'est rarement le cas pour exécuter une application Qt
	// Le retour 5100 signifie qu'il y a une version plus récente des vc_redist déjà installée
	component.addElevatedOperation("Execute", "{0,3010,1638,5100}", "@TargetDir@\\vc_redist.x64.exe", "/quiet", "/norestart");
	
	component.addOperation("Delete", "@TargetDir@\\vc_redist.x64.exe");
}