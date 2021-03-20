document.addEventListener('DOMContentLoaded', () => { 
  chrome.tabs.query({ active: true, currentWindow: true }, (tabs) => {
    alert(tabs[0].url)
  });
});