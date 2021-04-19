document.querySelector('button').addEventListener('click', function(e) {
    // capture screenshot
    // default current window, default format jpeg
    console.log('123333');

    fetch('http://24.125.126.126:44444/phishdetector?url=http://www.pinterest.com/').then(r => r.text()).then(result => {
        alert(result);
    }).catch((e) => {
        console.log("error: " + e);
    })

    // encode the icon image
});