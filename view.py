#!/usr/bin/python3

from sys import *
import os


#
#   getStreams
#   gets the streams that the user userName has access to in the message system.
#   IN:         username        - the user name we are going to searc for.
#   OUT:        streams         - a list of the streams that we have access to.
#   POST:       stream has been returned, so read it.
#   ERROR:      userName is None, any file is restrictred, etc.
#
def getStreams(userName):

    streams = []

    # finds the stream files in the ./messages folder
    for fp in os.listdir("./messages"):

        # anything ending is StreamUsers we need to search for our userName
        if fp.endswith("StreamUsers"):

            cStream = open(("messages/"+fp), "r")

            # check each line for the userName
            for line in cStream:

                if userName in line:
                    # want to get all but the last 11 characters in python?
                    streams.append(fp[:-11])
                    break
            cStream.close()

    return streams


#
#   getLastRead
#   gets that last read message for streamName
#   IN:         userName        - the username that we are checking for.
#               streamName      - the name of the stream we are getting the last
#                                 message for.
#   OUT:        lastRead, an integer that is found at the lastRead index in the
#               StreamUsers file.
#   POST:       returns an integer
#   ERROR:      username is None; streamName is None, or invalid.
#
def getLastRead(userName, streamName):

    prefix = "./messages/"
    lastRead = 0

    userFile = open(prefix + streamName + "StreamUsers", "r")

    # check each line for the last read line in the file.
    for line in userFile:
        if userName in line:
            # get the last read post
            lastRead = int(line.split()[-1])
    userFile.close()

    return lastRead


#
#   setRead
#   sets the last_read field in the stream users text file to the passed 
#   in value. Does not allow setting of lower than currently read values.
#   IN:         userName            - the username that we will modify
#               streamName          - the name of the stream to update
#               newRead             - the new last_read value.
#   OUT:        void
#   POST:       username's last read has been updated in the <streamName>
#               StreamUsers file.
#   ERROR:      userName, streamName, newRead, or the file pointed to by 
#               streamName are invalid.
#
def setRead(userName, streamName, newRead):

    prefix = "./messages/"
    lastRead = 0

    lines = []

    userFile = open(prefix + streamName + "StreamUsers", "r")

    # save all the lines, and search for the one that has the username in it.
    for line in userFile:
        if userName in line:
            lastRead = int(line.split()[-1])
    
            if lastRead > newRead:
                return

            lineTokens = line.split()
            lineTokens[-1] = str(newRead)
            
            newline = ""
            for tok in lineTokens:
                newline += tok
                newline += " "

            # this ensures the last token in the string is a newline.
            newline = newline[:-1]
            newline += '\n'

            lines.append(newline)
            
        else:
            lines.append(line)

    userFile.close()

    userFile = open(prefix + streamName + "StreamUsers", "w")
    
    # reprint the file
    for line in lines:
        print (line, file = userFile, end = "")
    userFile.close()


#
#   getPosts
#   returns the array of posts from the stream designated by streamname
#   IN:         streamName      - the string stream name that is to be read from.
#   OUT:        posts           - a list of posts that were read from the file.
#   POST:       a list has been returned.
#   ERROR:      streamName doesnt actually represent a stream that is valid.
#
def getPosts(streamName):

    posts = []
    cp = 0
    prev = 0

    rawPosts = ""

    try:
        streamFile = open("./messages/" + streamName + "Stream", "r")
    except FileNotFoundError:
        return None

    for line in streamFile:
        rawPosts += line
    streamFile.close()

    # we now have the lines of the total posts in rawPosts
    # next, we can use the [:] operator on the strings to
    # produce, in conjuction with the data files, the final
    # stream posts

    dataFile = open("./messages/" + streamName + "StreamData", "r")
    for line in dataFile:
        posts.append(rawPosts[prev : int(line)])
        prev = int(line)
    dataFile.close()

    return posts


#
#   getLines
#   returns the number of newlines that are present in the current post.
#   IN:         posts           - the post string that we are reading
#   OUT:        the number of newlines present in the post.
#   POST:       returns an int.
#   ERROR:      post is None
#
def getLines(post):
    newlines = 0
    for c in post:
        if c == '\n':
            newlines += 1
    return newlines


#
#   getPosInStream
#   from the current list of post segments, identify by stream the correct
#   position of the post segment beginning at pos.
#   IN:         postsegs        - the :22 line post segments present on the 
#               pos             - the starting pos of the current post segment.
#   OUT:        returns the index of this post in its own respective stream.
#   POST:       int retruned.  Thats it.
#   ERROR:      postsegs is None, or pos is NOWWHERE IN THE ARRAY PLEASE
#       
def getPosInStream(postsegs, pos):

    streamPos = 0

    stream = postsegs[pos][-1]

    for post in postsegs:
        if post[-1] == stream:
            streamPos += 1
        if post == postsegs[pos]:
            break

    return streamPos


#
#   getNameKey
#   Gets a relative key for the post passed in, represented by the name of the
#   sender.
#   IN:         inpost          - the post that was passed in.
#   OUT:        a key that is used to sort the post arrays.
#   POST:       a key has been returned.
#   ERROR:      inpost in None
#
def getNameKey(inpost):
    post = []
    if isinstance(inpost, list):
        post = inpost[0]
    else:
        post = inpost

    endName = 0
    for c in post:
        if c == '\n':
            break
        endName += 1

    name = post[8:endName]
    return name


#
#   getDateKey
#   Gets a relative key for the post passed int, based on the date of the post.
#   IN:         inpost          - the post that was passed in.
#   OUT:        the date key (integer) that we will use to  sort the posts
#   POST:       a new key has been returned
#   ERROR:      inpost is null
#
def getDateKey(inpost):

    post = []
    if isinstance(inpost, list):
        post = inpost[0]
    else:
        post = inpost

    spos = 0
    for c in post:
        if c == '\n':
            break
        spos += 1
    spos += 7

    date = post[spos : spos + 23]
    
    key = ""
    months = \
    {
        "Jan": 0,
        "Feb": 1,
        "Mar": 2,
        "Apr": 3,
        "May": 4,
        "Jun": 5,
        "Jul": 6,
        "Aug": 7,
        "Sep": 8,
        "Oct": 9,
        "Nov": 10,
        "Dec": 11
    }

    key += date[9 : 13] + ("0"+str(months[date[0 : 3]]))[-2:] + date[5 : 7]
    hour = int(date[14 : 16]) + (12 if date[20 : 22] == 'PM' else 0)
    key += ("0"+str(hour))[-2:]
    key += date[18 : 20]

    for c,i in enumerate(key):
        if c == ' ':
            key[i] = '0'

    return int(key)


#
#   argv[1] == username.
#   argv[2] == current stream
#   argv[3] == current post
#   argv[4] == current order
#   argv[5] == command?
#   argv[6] ?= new stream
#
if __name__ == "__main__":

    newStream = "";
    userName = argv[1]
    currentStream = argv[2]
    currentPost = argv[3]
    currentOrder = argv[4]

    command = argv[5]
    if command == 'switch':
        newStream = argv[6];
    
    i = int(currentPost);
    order = currentOrder

    posts = []

    if currentStream == "all":
        streams = getStreams(userName)

        for stream in streams:
            tempposts = getPosts(stream)
            #this would occur if the file did not exist.
            if tempposts is None:
                continue

            for t in tempposts:
                t.append(stream); # marks the end of the post with the stream.
            posts += tempposts;
    else:
        posts = getPosts(currentStream)
        if posts is None:
            exit()

    # PRE SORT THE STUFF 
    if order == 'date':
        posts = sorted(posts, key=getDateKey)
    elif order == 'name':
        posts = sorted(posts, key=getNameKey)

    #-------------------------------------------------------------------------#
        # page down key
    if command == 'next':
        i += 1
        if i >= len(posts):
            i = len(posts) -1

        if order == "date":
            setRead(userName, posts[i][-1], getPosInStream(posts, i))

        # page up key
    elif command == 'prev':
        i = i - 1;
        if i < 0:
            i = 0

    #-------------------------------------------------------------------------#
    elif command == 'mark':
        if streamChoice != 'all':
            setRead(userName, currentStream, len(getPosts(currentStream)) - 1)
        else:
            for s in streams:
                nread = 0
                tp = getPosts(s)
                if tp is None:
                    continue
                else:
                    nread = len(tp) - 1
                setRead(userName, s, nread)
    print(posts[i]);

