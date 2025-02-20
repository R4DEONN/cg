import AlchemyController from "../Controller/AlchemyController";
import IView from "./IView";
import Component from "../Component";
import ListView from "./ListView";
import ExperimentView from "./ExperimentView";
import Tag from "../Tag";

class AlchemyView extends Component {
	private _listView = new ListView();
	private _experimentView = new ExperimentView();

	constructor(
		private readonly _controller: AlchemyController,
	) {
		super({
			blockName: 'alchemy-container',
		});

		const title = new Component({
			blockName: 'title',
			blockTag: Tag.P,
		});
		title.setText("Alchemy");
		this.addChild(title);
		const tableWrapper = new Component({blockName: 'table-wrapper'});

		tableWrapper.addChild(this._listView);
		tableWrapper.addChild(this._experimentView);

		this.addChild(tableWrapper);
	}
}

export default AlchemyView;