# Burp Suite

## Overview

* Proxy - What allows us to funnel traffic through Burp Suite for further analysis
* Target - How we set the scope of our project. We can also use this to effectively create a site map of the application we are testing.
* Intruder - Incredibly powerful tool for everything from field fuzzing to credential stuffing and more
* Repeater - Allows us to 'repeat' requests that have previously been made with or without modification. Often used in a precursor step to fuzzing with the aforementioned Intruder
* Sequencer - Analyzes the 'randomness' present in parts of the web app which are intended to be unpredictable. This is commonly used for testing session cookies
* Decoder - As the name suggests, Decoder is a tool that allows us to perform various transforms on pieces of data. These transforms vary from decoding/encoding to various bases or URL encoding.
* Comparer - Comparer as you might have guessed is a tool we can use to compare different responses or other pieces of data such as site maps or proxy histories (awesome for access control issue testing). This is very similar to the Linux tool diff.
* Extender - Similar to adding mods to a game like Minecraft, Extender allows us to add components such as tool integrations, additional scan definitions, and more!
* Scanner - Automated web vulnerability scanner that can highlight areas of the application for further manual investigation or possible exploitation with another section of Burp. This feature, while not in the community edition of Burp Suite, is still a key facet of performing a web application test.

**Questions**

	1. Which tool in Burp Suite can we use to perform a 'diff' on responses and other pieces of data?

Comparer

	2. What tool could we use to analyze randomness in different pieces of data such as password reset tokens?

Sequencer

	3. Which tool can we use to set the scope of our project?

Target

	4. While only available in the premium versions of Burp Suite, which tool can we use to automatically identify different vulnerabilities in the application we are examining?

Scanner

	5. Encoding or decoding data can be particularly useful when examining URL parameters or protections on a form, which tool allows us to do just that?

Decoder

	6. Which tool allows us to redirect our web traffic into Burp for further examination?

Proxy

	7. Simple in concept but powerful in execution, which tool allows us to reissue requests?

Repeater

	8. With four modes, which tool in Burp can we use for a variety of purposes such as field fuzzing?

Intruder

	9. Last but certainly not least, which tool allows us to modify Burp Suite via the addition of extensions?

Extender

## Proxy

Gernerally speaking, proxy servers by allow us to relay traffic through an alternative route to the internet. Using a proxy for web application testing allows us to view and modify traffic inline at a granular level.

Currently web traffic is configured to route through our instance of Burp Suite meaning that Burp will intercept our traffic. This means:

* Requests will require authorization to be sent.
* We can modify our requests inline (similar to a man in the middle) and then send them on
* We can drop requests we don't want to be sent
* We can send these requests to other tools for modification

**Questions**

	1. By default, the Burp Suite proxy listens on only one interface. What is it? Use the format of IP:PORT

127.0.0.1:8080

In Burp Suite, navigate to the Intercept sub-tab of the Proxy section. Enable Intercept

Return to your web browser and navigate to the web application hosted on the VM we deployed just a bit ago. Note that the page appears to be continuously loading. Change back to Burp Suite, we now have a request that's waiting in our intercept tab. 
	
	3.Take a look at the actions, which shortcut allows us to forward the request to Repeater?

ctrl-r

	4. How about if we wanted to forward our request to Intruder?

ctrl-i

Burp Suite saves the history of requests sent through the proxy along with their varying details. This can be especially useful when we need to have proof of our actions throughout a penetration test or we want to modify and resend a request we sent a while back. 

	5. What is the name of the first section wherein general web requests (GET/POST) are saved?

HTTP history

	6. Defined in RFC 6455 as a low-latency communication protocol that doesn't require HTTP encapsulation, what is the name of the second section of our saved history in Burp Suite? These are commonly used in collaborate application which require real-time updates (Google Docs is an excellent example here).

Websockets history

Before we move onto exploring our target definition, let's take a look at some of the advanced customization we can utilize in the Burp proxy. Move over to the Options section of the Proxy tab and scroll down to Intercept Client Requests. Here we can apply further fine-grained rules to define which requests we would like to intercept. Perhaps the most useful out of the default rules is our only AND rule. 

	7. What is it's match type?

URL

	8. How about it's 'Relationship'? In this situation, enabling this match rule can be incredibly useful following target definition as we can effectively leave intercept on permanently (unless we need to navigate without intercept) as it won't disturb sites which are outside of our scope - something which is particularly nice if we need to Google something in the same browser.

Is in target scope

## Target Definition

The target tab in Burp allows the user to define the scope, view a site map and specify issue definitions.

When starting a web application test you'll likely be provided a few things

* The application URL (hopefully for dev/test and not prod)
* A list of the different user roles within the application
* Various test accounts and associated credentials for those accounts
* A list of pieces/forms in the application which are out-of-scope for testing and should be avoided

From this information we can start to define the scope of our attack.

**Questions**

Before leaving the Proxy tab, switch Intercept to disabled. We'll still see the pages we navigate to in our history and the target tab, just having Intercept constantly stopping our requests for this next bit will get old fast.

Navigate to the Target tab in Burp. In our last task, Proxy, we browsed to the website on our target machine (in this case OWASP Juice Shop). Find our target site in this list and right-click on it. Select 'Add to scope'. 

Clicking 'Add to scope' will trigger a pop-up. This will stop Burp from sending out-of-scope items to our site map.

Select 'Yes' to close the popup.

Browse around the rest of the application to build out our page structure in the target tab. Once you've visited most of the pages of the site return to Burp Suite and expand the various levels of the application directory. 

	1. What do we call this representation of the collective web application?

Site Map

	2. What is the term for browsing the application as a normal user prior to examining it further?

Happy Path

One last thing before moving on. Within the target tab, you may have noticed a sub-tab for issue definitions. Click into that now.

The issue definitions found here are how Burp Suite defines issues within reporting. While getting started, these issue definitions can be particularly helpful for understanding and categorizing various findings we might have. 

	3. Which poisoning issue arises when an application behind a cache process input that is not included in the cache key?

Web Cache Poisoning

## Repeater

Repeater allow us to repeat requests we've already made. The can be resent as-is or they can be modified. 

**Questions**

	1. Firstly I'll try logging in with invalid credentials. What error is generated when login fails?

Invalid email or password.

But wait, didn't we want to send that request to Repeater? Even though we didn't send it to Repeater initially via intercept, we can still find the request in our history. Switch over to the HTTP sub-tab of Proxy. Look through these requests until you find our failed login attempt. Right-click on this request and send it to Repeater and then send it to Intruder, too!

	2. Now that we've sent the request to Repeater, let's try adjusting the request such that we are sending a single quote (') as both the email and password. What error is generated from this request?

SQLITE_ERROR:

Now that we've leveraged Repeater to gain proof of concept that Juice Shop's login is vulnerable to SQLi, let's try something a little more mischievous and attempt to leave a devastating zero-star review. First, click on the drawer button in the top-left of the application. If this isn't present for you, just skip to the next question.


Next, click on 'Customer Feedback' (depending on the version of Juice Shop this also might be along the top of the page next to 'Login' under 'Contact Us')

With the Burp proxy on submit feedback. Once this is done, find the POST request in your HTTP History in Burp and send it to Repeater.

	3. What field do we have to modify in order to submit a zero-star review?

Rating

Submit a zero-star review and complete this challenge in Juice Shop!

## Intruder

Intruder can be used for many things ranging from fuzzing to brute-forcing. It is mainly used for automation. 

Common use cases for the intruder module include

* Enumerating identifiers such as usernames, cycling through predictable session/password recovery tokens, and attempting simple password guessing
* Harvesting useful data from user profiles or other pages of interest via grepping our responses
* Fuzzing for vulnerabilities such as SQL injection, cross-site scripting (XSS), and file path traversal

To accomplish these use cases, intruder has four different attack types:

* Sniper - The most popular attack type, this cycles through our selected positions, putting the next available payload (item from our wordlist) in each position in turn. This uses only one set of payloads (one wordlist).
* Battering Ram - Similar to Sniper, Battering Ram uses only one set of payloads. Unlike Sniper, Battering Ram puts every payload into every selected position. Think about how a battering ram makes contact across a large surface with a single surface, hence the name battering ram for this attack type.
* Pitchfork - The Pitchfork attack type allows us to use multiple payload sets (one per position selected) and iterate through both payload sets simultaneously. For example, if we selected two positions (say a username field and a password field), we can provide a username and password payload list. Intruder will then cycle through the combinations of usernames and passwords, resulting in a total number of combinations equalling the smallest payload set provided. 
* Cluster Bomb - The Cluster Bomb attack type allows us to use multiple payload sets (one per position selected) and iterate through all combinations of the payload lists we provide. For example, if we selected two positions (say a username field and a password field), we can provide a username and password payload list. Intruder will then cycle through the combinations of usernames and passwords, resulting in a total number of combinations equalling usernames x passwords. Do note, this can get pretty lengthy if you are using the community edition of Burp. 

Let's return to the SQL injection vulnerability that we found

**Questions**

	1. Which attack type allows us to select multiple payload sets (one per position) and iterate through them simultaneously?

Pitchfork

	2. How about the attack type which allows us to use one payload set in every single position we've selected simultaneously?

Battering Ram

	3. Which attack type allows us to select multiple payload sets (one per position) and iterate through all possible combinations?

Cluster Bomb

	4. Perhaps the most commonly used, which attack type allows us to cycle through our payload set, putting the next available payload in each position in turn?

Sniper

Return to the Intruder in Burp. In our previous task, we passed our failed login attempt to both Repeater and Intruder for further examination. Open up the Positions sub-tab in the Intruder tab with this request now and verify that 'Sniper' is selected as our attack type.

Burp attempts to automatically highlight possible fields of interest for Intruder, however, it doesn't have it quite right for what we'll be looking at in this instance. Hit 'Clear' on the right-hand side to clear all selected fields.

Next, let's highlight the email field between the double quotes ("). This will be whatever you entered in the email field for our previous failed login attempt.

Now click 'Add' to select our email field as a position for our payloads.

Next, let's switch to the payloads sub-tab of Intruder. Once there, hit 'Load' and select the wordlist you previously downloaded in question five that is attached to this task.

Almost there! Scroll down and uncheck 'URL-encode these characters'. We don't want to have the characters sent in our payloads to be encoded as they otherwise won't be recognized by SQL.

	5. Finally, click 'Start attack'. What is the first payload that returns a 200 status code, showing that we have successfully bypassed authentication?

a' or 1=1--

## Sequencer 

Burps sequencer is a tool for analyzing the quality of randomness in session tokens, or other important data items that are otherwise intended to be unpredictable.

**Questions**

Switch over to the HTTP history sub-tab of Proxy. 

We're going to dig for a response which issues a cookie. Parse through the various responses we've received from Juice Shop until you find one that includes a 'Set-Cookie' header. 

Once you've found a request response that issues a cookie, right-click on the request and select 'Send to Sequencer'.

Change over Sequencer and select 'Start live capture'

Let Sequencer run and collect \~10,000 requests. Once it hits roughly that amount hit 'Pause' and then 'Analyze now'

	1. Parse through the results. What is the effective estimated entropy measured in?

Bits

	2. In order to find the usable bits of entropy we often have to make some adjustments to have a normalized dataset. What item is converted in this process?

Token

## Decoder and Comparer

Decoder is a tool that allows us to perform various transforms on pieces of data. These transforms vary from decoding/encoding to various bases or URL encoding.

Comparer is used to compare different responses or other pieces of data. 

**Questions**

Let's first take a look at decoder by revisiting an old friend. Previously we discovered the scoreboard within the site JavaScript. Return to our target tab and find the API endpoint highlighted in the following request:

Copy the first line of that request and paste it into Decoder. Next, select 'Decode as ...' URL

	1. What character does the %20 in the request we copied into Decoder decode as?

Space

	2. Similar to CyberChef, Decoder also has a 'Magic' mode where it will automatically attempt to decode the input it is provided. What is this mode called? 

Smart Decode

	3. What can we load into Comparer to see differences in what various user roles can access? This is very useful to check for access control issues.

Site Maps

	4. Comparer can perform a diff against two different metrics, which one allows us to examine the data loaded in as-is rather than breaking it down into bytes?

Words

## Extender

Install extensions from the store or create them manually.

Must set up Jython standalone under Python environment

## There's more

Before we conclude, let's have a quick look at some premium features.

One of the most powerful features in Burp Suite, the Burp Suite scanner allows us to passively and actively scan and spider the website wee are testing for vulnerabilities. A report will be created that can then be analysed

Commonly used in manual tests, Burp Collaborator Client allows us to gain insight into issues that may otherwise seem to produce no output.

**Questions**

	1. Download the report attached to this task. What is the only critical issue?

Cross-origin resource sharing: arbitrary origin trusted

	2. How many 'Certain' low issues did Burp find?

12