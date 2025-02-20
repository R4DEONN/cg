import Component from "../Component";
import Tag from "../Tag";

class ExperimentView extends Component {
	constructor() {
		super({
			blockName: 'experiment-view',
		});

		const title = new Component({
			blockTag: Tag.P,
		});
		title.setText("Поле для экспериментов");
		this.addChild(title);
	}
}

export default ExperimentView;