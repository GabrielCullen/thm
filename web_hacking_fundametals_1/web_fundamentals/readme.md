# Web Fundamentals

## How do we load websites?

Initially a DNS request is made. A DNS is like a giant phonebook that turns a URL into an IP address. An IP address uniquely identifies each internet connected device. Once the browser knows the servers IP address, it can ask for the web page through a HTTP GET request. For most websites, these requests will usee HTTPS which is an encrypted version of HTTP. This uses TLS 1.3 encryption which means it is possible to communicate without other parties being able to read or modify the data.

A web server is software that receives and responds to HTTP(S) requests. By default HTTP runs on port 80, and HTTPS run on port 443. If these ports are open, it's likely that a website is being hosted that can be examined.

**Questions**

	1. What request verb is used to retrieve page content?

GET

	2. What port do web servers normally listen on?

80

	3. What's responsible for making websites look fancy?

CSS

## More HTTP - Verbs and request formats

There are 9 different HTTP verbs, each one has a different function.

* GET requests are used to retrieve content
* POST requests are used to send data to a web server

There are more verbs but these are not as commonly used. 

An HTTP request can be broken down into parts. The first line is a verb and a path for the server. Next there are headers which give the web server more information about the request. Cookies are also sent in the request headers. For POST requests, the body contains the content that will be sent to the server, for GET requests, a body is allowed but will likely be ignored by the server.

Information can be retrieved from the headers which is useful for forensics.

The server should reply with a response that follows a similar structure to the request, but the first line describes the status - normally a code.

* 100 - 199: Information
* 200 - 299: Success
* 300 - 399: Redirects
* 400 - 499: Client Errors
* 500 - 599: Server Errors

The response will also have a body. For GET requests, this is normally web content or information such as JSON. For POST requests, it may be a status message or similar.

**Questions**

	1. What verb would be used for a login?

POST

	2. What verb would be used to see your bank balance once you're logged in?

GET

	3. Does the body of a GET request matter? Yea/Nay

Nay

	4. What's the status code for "I'm a teapot"?

418

	5. What status code will you get if you need to authenticate to access some content, and you're unauthenticated?

401

## Cookies

Cookies are small bits of data that are stored in your browser. They have a huge number of uses, but the most common involve session management or advertising. Cookies are normally sent with every HHTTP request made to a server.

Since HTTP is stateless, cookies are needed in order to keep track of this. The allow websites to keep track of relevant data and display it to you.

Cookies contain a name (identifier), a value (where data is stored), an expiry date (when the browser should remove this cookie) and a path (what requests the cookie should be sent with).

The server normally sets cookies, but these can also be set for JavaScript inside the browser. A cookie should only communicate with the website that set them. Unless it's an advertising/tracking cookie.

When you log into a web application you are given a session token. This allows the web server to identify your requests from other users. If you can obtain someone else's session token then you are able to impersonate them.

You can manipulate cookies using developer tools and you can also create your own if necessary.

## Mini CTF

You can make HTTP requests without browsers, cURL can be used for this

By default it will perform GET requests on the url it is provided.

The -X flag can be used to specify the request type

curl -X POST --data (data)

curl does not store cookies, you have to specify any cookies and values that you would like to send with your request.

**Questions**

There's a web server running on http://10.10.77.119:8081. Connect to it and get the flags!

* GET request. Make a GET request to the web server with path /ctf/get
* POST request. Make a POST request with the body "flag_please" to /ctf/post
* Get a cookie. Make a GET request to /ctf/getcookie and check the cookie the server gives you	
* Set a cookie. Set a cookie with name "flagpls" and value "flagpls" in your devtools (or with curl!) and make a GET request to /ctf/sendcookie

######

	1. What's the GET flag

thm{162520bec925bd7979e9ae65a725f99f}

	2. What's the POST flag?

thm{3517c902e22def9c6e09b99a9040ba09}

	3. What's the "Get a cookie" flag?

thm{91b1ac2606f36b935f465558213d7ebd}

	4. What's the "Set a cookie" flag?

thm{c10b5cb7546f359d19c747db2d0f47b3}