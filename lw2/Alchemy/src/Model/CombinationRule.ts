import {AlchemyElementType} from "./ElementsList";

export type CombinationRule = {
	ingredients: string[];
	results: string[];
}

export const CombinationRules: CombinationRule[] = [
	{ingredients: [AlchemyElementType.FIRE, AlchemyElementType.WATER], results: [AlchemyElementType.STEAM]},
	{ingredients: [AlchemyElementType.FIRE, AlchemyElementType.EARTH], results: [AlchemyElementType.LAVA]},
	{ingredients: [AlchemyElementType.AIR, AlchemyElementType.EARTH], results: [AlchemyElementType.DUST]},
	{ingredients: [AlchemyElementType.FIRE, AlchemyElementType.DUST], results: [AlchemyElementType.POWDER]},
	{ingredients: [AlchemyElementType.FIRE, AlchemyElementType.POWDER], results: [AlchemyElementType.EXPLOSION, AlchemyElementType.SMOKE]},
	{ingredients: [AlchemyElementType.AIR, AlchemyElementType.FIRE], results: [AlchemyElementType.ENERGY]},
	{ingredients: [AlchemyElementType.LAVA, AlchemyElementType.WATER], results: [AlchemyElementType.STEAM, AlchemyElementType.STONE]},
	{ingredients: [AlchemyElementType.AIR, AlchemyElementType.ENERGY], results: [AlchemyElementType.STORM]},
	{ingredients: [AlchemyElementType.FIRE, AlchemyElementType.STONE], results: [AlchemyElementType.METAL]},
]