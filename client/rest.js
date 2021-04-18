document.querySelector('button').addEventListener('click', function(e) {
    // capture screenshot
    // default current window, default format jpeg
    console.log('123333');

    fetch('http://24.125.126.126:44444/phishdetector?url=www.baidu.com').then(r => r.text()).then(result => {
        alert(result);
    })

    // encode the icon image
});