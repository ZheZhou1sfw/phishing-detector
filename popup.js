chrome.tabs.query({active: true, currentWindow:true}, function(tabs)
{
    // step 1: get the url
    let url = tabs[0].url;
    // step 2: perform checks

    // step 3: render result

    document.getElementById("level").innerHTML = url;
});


