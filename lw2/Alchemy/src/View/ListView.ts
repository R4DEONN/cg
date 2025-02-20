import Component from "../Component";
import Tag from "../Tag";

class ListView extends Component {
	constructor() {
		super({
			blockName: "list-view",
		});

		const title = new Component({
			blockTag: Tag.P,
		});
		title.setText("Открытые элементы");
		this.addChild(title);
	}
}

export default ListView;