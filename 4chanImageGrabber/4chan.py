#! /usr/bin/python3
#AUTHOR : KEVIN PLUAS

# A small & lightweight 4chan image downloader.
# To operate, give the program the link to the ACTIVE thread and
# it will download every single image in its original size and format.
# After downloading, it will save the images in the current working directory
import re
from select import select
import requests, bs4, os

# http://boards.4channel.org/g/thread/51971506 - The test thread
# class = fileThumb   / This seems to come before every thumbnail with the actual image and respective image link
thread_URL = input("Please enter the COMPLETE URL of the thread with images you want to download:\n")

#Quit program on empty input
if not thread_URL : 
    print("Nothing entered\n")
    quit()

#Creates a directory for the images
os.makedirs("threadImages", exist_ok=True)
#Stores the HTML content in a string using requests
thread_download = requests.get(thread_URL)

# Checks for errors while requesting the URL
try:
    thread_download.raise_for_status()
except Exception as exc:
    print("There was a problem: %s" % (exc))
    quit()


#Beautiful Soup (BS4) is used to actually parse the HTML string
thread_soup = bs4.BeautifulSoup(thread_download.text, features="html.parser")

thread_class_fileThumb = thread_soup.select('a[class = "fileThumb"]')
#Will only take the elements http://is2.4chan.org/g/1450659832892.png
#with the 'a' tag and class attribute = 'fileThumb'
#The subsequent href is the URL for the full size image

img_tags = thread_soup.select('img')
urls = [img['src'] for img in img_tags]

for url in urls:
    filename = re.search(r'/([\w_-]+[.](jpg|gif|png))$', url)
    if not filename:
         print("Regex didn't match with the url: {}".format(url))
         continue
    with open(filename.group(1), 'wb') as f:
        if 'http' not in url:
            # sometimes an image source can be relative 
            # if it is provide the base url which also happens 
            # to be the site variable atm. 
            url = '{}{}'.format(thread_URL, url)
        response = requests.get(url)
        f.write(response.content)
        print("Downloading : " + url)
        
print("Done!")