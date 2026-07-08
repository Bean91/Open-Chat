import React, {useEffect, useRef, useState} from "react";
import { useParams } from "react-router";
import Markdown from 'react-markdown';
import 'github-markdown-css/github-markdown.css';
import remarkGfm from 'remark-gfm';
import { Prism as SyntaxHighlighter } from "react-syntax-highlighter";
import { oneDark } from "react-syntax-highlighter/dist/cjs/styles/prism";
import '../style.css';

interface docs {
	sec: boolean,
	ite: boolean
}

const components = {
	// @ts-expect-error ignore
	code({ node, inline, className, children, ...props }) {
		const match = /language-(\w+)/.exec(className || '');
		if (!inline && match) {
			return (
				<SyntaxHighlighter
					style={oneDark}
					language={match[1]}
					PreTag="div"
					{...props}
					>
					{String(children).replace(/\n$/, '')}
				</SyntaxHighlighter>
			);
		}
		return (
			<code className={className} {...props}>
				{children}
			</code>
		);
	},
};

const MDContent: React.FC<docs> = ({sec, ite}) => {
	const sidebar = useRef<HTMLDivElement | null>(null);
	const { section, item } = useParams();
	const [content, setContent] = useState<string>("");
	const [sectionsList, setSectionsList] = useState<string[]>([""]);
	const [itemsList, setItemsList] = useState<string[][]>([[""]]);

	const classes = "cursor-pointer py-1 pt-1.5 px-2 rounded-sm my-1"

	useEffect(() => {
		fetch("https://raw.githubusercontent.com/bean91/open-chat/main/docs/docslist.txt", {
			"method": "GET",
		})
		.then(response => response.text())
		.then(data => {
			const parsedData: string[] = data.split("\n");
			setSectionsList(JSON.parse(parsedData[0]));
			setItemsList(JSON.parse(parsedData[1]));
		});
		if (sec && !ite) {
			fetch(`https://raw.githubusercontent.com/bean91/open-chat/main/docs/AIUsage.md`, {
				"method": "GET"
			}).then(response => response.text()).then(data => {setContent(data);});
		} else if (!sec && !ite) {
			fetch(`https://raw.githubusercontent.com/bean91/open-chat/main/docs/introduction.md`, {
				"method": "GET"
			}).then(response => response.text()).then(data => {setContent(data);});
		} else if (sec && ite) {
			fetch(`https://raw.githubusercontent.com/bean91/open-chat/main/docs/${section}/${item}.md`, {
				"method": "GET"
 			}).then(response => response.text()).then(data => {setContent(data);});
 		}
	}, [section, item, sec, ite]);

	useEffect(() => {
		setContent(content.replace(".md", ""));
	}, [content])

	useEffect(() => {
		if (sidebar.current) {
			if (!sec && !ite) {
				sidebar.current.innerHTML = `<p class="${classes} bg-gray-700"><a>Introduction</a></p><p class="${classes}"><a href="/docs/aiusage">AI Usage</a></p>`;
			} else if (sec && !ite) {
				sidebar.current.innerHTML = `<p class="${classes}"><a href="/docs">Introduction</a></p><p class="${classes} bg-gray-700"><a>AI Usage</a></p>`;
			} else {
				sidebar.current.innerHTML = `<p class="${classes}"><a href="/docs">Introduction</a></p><p class="${classes}"><a href="/docs/aiusage">AI Usage</a></p>`;
			}
		}
	}, [section, item, sec, ite, sidebar, classes])

	useEffect(() => {
		if (sidebar.current) {
			for (let i = 0; i < sectionsList.length; i++) {
				if (sectionsList[i] === section) {
					sidebar.current.innerHTML += `<div id="${sectionsList[i]}"><h4 class="p-1 rounded-sm bg-gray-700">${sectionsList[i]}</h4>`;
					for (let j = 0; j < itemsList[i].length; j++) {
						if (itemsList[i][j] === item) {
							sidebar.current.innerHTML += `<p class="${classes} text-sm ml-4 bg-gray-700"><a href="/docs/${sectionsList[i]}/${itemsList[i][j]}">${itemsList[i][j]}</a></p>`;
						} else {
							sidebar.current.innerHTML += `<p class="${classes} text-sm ml-4"><a href="/docs/${sectionsList[i]}/${itemsList[i][j]}">	${itemsList[i][j]}</a></p>`;
						}
					}
					sidebar.current.innerHTML += `</div>`;
				} else {
					sidebar.current.innerHTML += `<div id="${sectionsList[i]}"><h4 class="${classes}">${sectionsList[i]}</h4>`;
					for (let j = 0; j < itemsList[i].length; j++) {
						sidebar.current.innerHTML += `<p class="${classes} text-sm ml-4"><a href="/docs/${sectionsList[i]}/${itemsList[i][j]}">	${itemsList[i][j]}</a></p>`;
					}
					sidebar.current.innerHTML += `</div>`;
				}
			}
		}
	}, [sectionsList, itemsList, sidebar, classes, section, item])

	return (
		<div className={"mt-16 grid grid-cols-5"}>
			<div ref={sidebar} className={"col-span-1 p-2 m-1 mr-0 bg-gray-600 text-white rounded-md h-fit"}></div>
			<article className={"markdown-body p-4 col-span-4 rounded-md"} style={{margin: "calc(var(--spacing))"}}>
				<Markdown
					remarkPlugins={[remarkGfm]}
					//@ts-expect-error ignore
					components={components}
				>{content}</Markdown>
			</article>
		</div>
	)
}

export default MDContent;
