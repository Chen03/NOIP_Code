// ==UserScript==
// @name         jzoj material
// @namespace    http://tampermonkey.net/
// @version      0.1
// @description  try to take over the world!
// @author       You
// @match        https://jzoj.net/*
// @grant        none
// ==/UserScript==

(function() {
    'use strict';
    document.head.innerHTML+="<style>a{outline:none !important;-webkit-transition: background-color .3s,-webkit-box-shadow .5s;transition: background-color .3s,-webkit-box-shadow .5s;transition: background-color .3s,box-shadow .5s;transition: background-color .3s,box-shadow .5s,-webkit-box-shadow .5s;-webkit-transition-timing-function: cubic-bezier(.39,.575,.565,1);transition-timing-function: cubic-bezier(.39,.575,.565,1);cursor: pointer;-webkit-user-select: none;-moz-user-select: none;-ms-user-select: none;user-select: none} .nav_bar a{padding: 8px;display:table;border-left: 3px solid transparent;border-color: transparent;}.active a{background-color:#eeeeee;border-color: #ed5f82}a:hover{border-color: #08c} .navbar-inner a{    display: table;    border-top: 3px solid transparent;    border-top-color: transparent;    -webkit-transition: border-color .2s,background .2s,color .2s;    transition: border-color .2s,background .2s,color .2s;        transition-timing-function: ease, ease, ease;    -webkit-transition-timing-function: cubic-bezier(.215,.61,.355,1);    transition-timing-function: cubic-bezier(.215,.61,.355,1);    position: relative;}  .navbar .nav > li > a:focus, .navbar .nav > li > a:hover{    border-top-color: #5f9fd6;    background: #f6f6f6;} .navbar-inner{background-image: none;border-radius: 0;    box-shadow: 0 0 0; border: 1px solid #fff;}</style>";
    var navEle=document.getElementById("navigation");
    navEle.className="nav pull-left"
})();