import express from "express"
// var express = require("express")
import fs from "fs"
// var fs = require("fs")
import * as convert from "xml-js"
// var convert = require("xml-js")
import XMLHttpRequest from "xhr2"
const app = express()
let deviceAddr = "http://192.168.197.176"

const keyboard = ["esc", "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9", "f10", "f11", "f12", "backspace", 
    "\\", "]", "[", "p", "o", "i", "u", "y", "t", "r", "e", "w", "q", "tab",
    "capslock", "a", "s", "d", "f", "g", "h", "j", "k", "l", ";", "'", "enter", 
    "shift", "/", ".", ",", "m", "n", "b", "v", "c", "x", "z", "shift",
    "ctrl", "win", "alt", "space", "alt", "win", "ctrl", "fn"]


app.listen(3001)
let allShortcuts;
let commands;
let tools;
fs.readFile("C:\\Program Files\\Adobe\\Adobe Photoshop 2022\\Locales\\en_US\\Support Files\\Shortcuts\\Win\\Default Keyboard Shortcuts.kys", "utf8", function (err, txt) {
    // console.log(txt);
    var result1 = convert.xml2json(txt, { compact: true, spaces: 4 });
    // var result2 = convert.xml2json(txt, { compact: false, spaces: 4 });

    allShortcuts = JSON.parse(result1);
    commands = allShortcuts['photoshop-keyboard-shortcuts'].command;
    tools = allShortcuts['photoshop-keyboard-shortcuts'].tool;
    console.log(commands[0], tools[0]);
})

app.post("/", (req, res) => {
    let data = ""
    req.on("data", (info) => {
        data += info;
    })
    req.on("end", () => {
        let obj = JSON.parse(data)
        let descriptor = JSON.parse(obj.descriptor)
        let letter = ""
        if (descriptor._target) {
            letter = getShortcut(convertCases(descriptor._target[0]._ref));
            console.log(letter, convertCases(descriptor._target[0]._ref));
            if (letter) {
                console.log(deviceAddr + "/" + keyboard.indexOf(letter.toLowerCase()));

                if (keyboard.indexOf(letter.toLowerCase()) >= 0) fetch(deviceAddr + "/" + keyboard.indexOf(letter.toLowerCase()));
                console.log(deviceAddr + "/" + keyboard.indexOf(letter.toLowerCase()));
            }

            // var oReq = new XMLHttpRequest();
            // oReq.open(deviceAddr + "/" + keyboard.indexOf(letter.toLowerCase()));
            // oReq.send();
        }

        // let response = await 

        // if (response.ok) { // if HTTP-status is 200-299
        //     // get the response body (the method explained below)
        //     let json = await response.json();
        // } else {
        //     alert("HTTP-Error: " + response.status);
        // }
    })
})

function convertCases(text) {
    const result = text.replace(/([A-Z])/g, " $1");
    const finalResult = result.charAt(0).toUpperCase() + result.slice(1);
    return finalResult;
}

function getShortcut(name) {
    let res = ""
    let found = commands.find(elem => elem._attributes.name == name)
    if (found) {
        res = found.shortcut.text;
    } else {
        found = tools.find(elem => elem._attributes.name == name)
        if (found) {
            res = found._text;
        }
    }
    return res;
}