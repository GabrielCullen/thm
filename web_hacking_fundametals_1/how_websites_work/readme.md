# How Websites Work

When you visit a website, your browser makes a request to a web server asking for information about the page you're visiting and will respond with data that your browser uses to show you the page; a web server is just a dedicated computer somewhere else in the world that handles your requests.

There are two major components that make up a website:
* Front End (Client-Side) - the way your browser renders a website.
* Back End (Server-Side) - a server that processes your request and returns a response.

**Questions**

    1. What term describes the way your browser renders a website?   

Front End

## HTML

Websites are primarily created using:
* HTML - To build websites and define their structure
* CSS - To make websites look pretty by adding styling options
* JavaScript - Implement complex features on pages using interactivity

HTML is the language websites are written in. Elements are the building blocks of HTML pages and tells the browser how to display content.

Tags contain attributes such as the `class` attribute which can be used to style an element, or the `src` attribute, which is used to specify the location of an image. An element can have multiple attributes each with it's own unique purpose.

**Questions**

    1. One of the images on the cat website is broken - fix it and the image will reveal the hidden text answer!

htmlhero

    2. Add a dog image to the page by adding another img tag (<img>) on line 11. The dog image location is img/dog-1.png

doghtml

## JavaScript

JavaScript is one of the most popular coding languages in the world and allows pages to become interactive. JS can dynamically update the page in real time, giving functionality for style changes, or to display moving animations.

JavaScript can be executed between `<script>` tags but can also be included remotely with `<script src="path/to/js_file.js"></script>`

**Questions**

    1. Click the "View Site" button on this task. On the right-hand side, add JavaScript that changes the demo element's content to "Hack the Planet"

JSISFUN

```html
<script type="text/javascript">
            document.getElementById("demo").innerHTML = "Hack the Planet";
        </script>
```

    2. Add the button HTML from this task that changes the element's text to "Button Clicked" on the editor on the right, update the code by clicking the "Render HTML+JS Code" button and then click the button.

```html
<button onclick='document.getElementById("demo").innerHTML = "Button Clicked";'>Click Me!</button>
```

## Sensitive Data Exposure

Sensitive Data Exposure is when a website doesn't properly protect (or remove) sensitive clear-text information to the end-user; usually found in the front-end source code of sites.

Sensitive information can be leveraged to gain access to the webpage - if there are login credentials hidden in the source code these could be used to gain access to the website. Even worse these credentials may be used for back-end components of the website.

**Questions**

    1. View the website on this task. What is the password hidden in the source code?

testpasswd

## HTML Injection

HTML Injection is a vulnerability that occurs when unfiltered user input is displayed on the page. If a website fails to sanitize user input, an attacker can inject HTML code into a vulnerable website.

Input sanitization is very important in order to keep a website secure. When the user is in control of how their input is displayed, the can submit HTML or Javascript code and the browser will use it on the page, allowing the user to control the pages appearance and functionality.

**Questions**

    1. View the website on this task and inject HTML so that a malicious link to http://hacker.com is shown.

HTML_INJ3CTI0N

```html
<a href="http://hacker.com">Nice link m8</a>
```