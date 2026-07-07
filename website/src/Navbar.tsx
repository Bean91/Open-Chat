import React from "react";
import "./style.css";

interface NavbarProps {
	location: string;
}

const Navbar: React.FC<NavbarProps> = ({ location }) => {
	const items: string[] = ["Home", "Docs", "GitHub"]
	const itemClass: string = "p-2.5 h-12 m-2 cursor-pointer rounded-md text-white text-xl font-medium items-center hover:bg-[#5b6372]";

	interface locations {
		[key: string]: string;
	}

	const locationList: locations = {
		"Home": "/",
		"Docs": "/docs",
		"GitHub": "https://github.com/Bean91/Open-Chat"
	};

	const changePlace = (item: string) => {
		if (item !== location) {
			window.location.href = locationList[item];
		}
	}

	return (
		<div className={"flex bg-gray-600 h-16 justify-between fixed top-0 inset-x-0"}>
			<div className={"w-3/4"}></div>
			{items.map((item: string, key: number) => (
				<div onClick={() => {changePlace(item)}} className={(location === item) ? `bg-gray-700 ${itemClass}` : `${itemClass} bg-gray-500`} key={key}>
					<p>{item}</p>
				</div>
			))}
			<div className={"w-1/8"}></div>
		</div>
	);
}

export default Navbar