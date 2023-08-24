
const puppeteer = require('puppeteer');
async function timeout(ms) {

	return new Promise(resolve => setTimeout(resolve, ms));	
	}
	

(async() => {
let browser = await puppeteer.launch({
		headless: true,
		executablePath: '/usr/bin/chromium-browser',
		  // args:['--no-sanbox', '--disable-setuid-sandbox']
	});

	const page = await browser.newPage();
	await page.goto('http://172.29.43.47');
	await timeout(5000);
	await page.setViewport({width:250, height: 122});
	await page.screenshot({path:'/var/www/html/eink.jpg'});
	await browser.close();

}) ();
