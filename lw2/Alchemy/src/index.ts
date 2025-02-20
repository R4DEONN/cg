import AlchemyController from "./Controller/AlchemyController";
import AlchemyView from "./View/AlchemyView";
import AlchemyModel from "./Model/AlchemyModel";

function main() {
	const alchemyModel = new AlchemyModel();
	const alchemyController = new AlchemyController(alchemyModel);
	const alchemyView = new AlchemyView(alchemyController);

	document.getElementById('content')?.appendChild(alchemyView.render());
}

main();