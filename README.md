### Warning: glOMP engine is early in development and may change in drastic ways within a short time.  While I welcome comments, contributions, and participation, I can't recommend its use for anything serious until more work is complete.

GLOMP engine
============

Experimental cross-platform graphical Lua game and multimedia engine built on OpenFrameworks.  The engine will use a variation of hierarchical MVC, event driven programming, and some light functional tricks to make development rapid and reusable. I am taking heavy inspiration from the wonderful Backbone.js and Underscore.js projects available for javaScript. 

Project Homepage (coming soon, linked for reference/bookmarking):  
[http://onemorepoint.com/glomp/](http://onemorepoint.com/glomp/)

Dependencies
------------

[OpenFrameworks 0071](http://www.openframeworks.cc/)

[Lua 5.2](http://www.lua.org/)

Platform Information
--------------------

### OS X

XCode 4 is awful. For that reason, the recommended way to compile the glOMP source in OS X is to copy the /core/src/ and /core/bin/ directories into an existing OpenFrameworks example using their download.  You will also then need to statically link Lua 5.2 into the project.

I use a small shell script to copy the files back out and into the git repo for commits. Gross? Yes. Blame Apple.

For those just wanting to use the engine, however, I will be providing binaries later on in development.

### Windows and Linux

Both above platforms SHOULD work with the source in this repo.  Once I move a bit further along in development, I will test that theory.

### Android, IOS

I hope to support releases for Android and IOS as well, as OpenFrameworks supports them.  The only roadblock here will be supporting the mobile OpenGL implementations.  However, at least for the initial 2D release, this should not be a problem.

