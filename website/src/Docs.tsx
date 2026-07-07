import Navbar from './Navbar.tsx';
import { Outlet } from "react-router";
import { useTitle } from "./hooks/useTitle.ts";
import MDContent from "./docs/MDContent.tsx";
import React from "react";
import './style.css';

interface docs {
  section: boolean,
  item: boolean
}

const Docs: React.FC<docs> = ({section, item}) => {
  useTitle("Docs | Open Chat");

  return (
    <div>
      <Navbar location={"Docs"} />
      <MDContent sec={section} ite={item} />
      <Outlet />
    </div>
  )
}

export default Docs;