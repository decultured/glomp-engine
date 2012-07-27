Base Types
==========

Identifier
----------

	Name, Type
	Used for lookups, bindings, and data persistence.  Basically a handle.
	An Identifier is a special data type in glOMP
	Names are usually automatically generated, types must be set and must be unique

Detail
------

	Store Information as Attributes
		Attributes are accessed through "get" and "set"
		Attributes are by default arbitrary and unregulated
	Have an Identifier
	Can be persisted (saved and loaded):
		Attributes and Listener Identifiers
	Owned and controlled by the developer
		(the engine will never change a value in a Resource)

DetailCollection
----------------

	Simply a list of Resources
	Used for organization

Actor
-----

	Have Resources and Elements (stored as Identifiers)
	Act as a mediator between Resources, other representations and Agents
	Usually perform Actions on Views based on changes in a model
	Can be persisted:
		List of Resource and View Identifiers
	Can Have Children
	Can be contained within other Actors
	Can be extended from other Actors

Agent
-----

	Store information as hidden Properties
		Property fields are fixed and typed
		Property fields are only set through Actions
		Properties might be other Agents
	Have a Identifier
	Can be persisted
	Owned and controlled by the engine
		(the engine might change values of a Agent)
	Actions act on a Agent
	Can sometimes have child representations
	Can be persisted
		Properties and Listener Identifiers
	May emit events

Globals
=======

A few globals are provided and maintained by the system:

### Resources ###

__Mouse__

+ Handles mouse input events and state
+ Behaves like an auto-syncing Resource
+ Attributes: 
	+ Buttons [1-4]
	+ X Pos
	+ Y Pos

__Keyboard__

+ Handles keyboard input events and state, behaves like an auto-syncing Resource
+ Attributes:
	+ Key States

__Window__

+ Handles window state and changes, also an auto-syncing Resource
+ Attributes:
	+ width
	+ height
	+ focused

### Actors ###

__App__

+ Event Transmitter only
+ Acts like an Actor

### Agents ###

__Scene__

+ An Agent that only exists as a root for other Agents.
+ Easy way to build a scene-graph.
+ Most Agents are not visible unless a child of this or guiscene.

__GuiScene__

+ Created for convenience, it is an Agent that only exists to store other Agents.
+ Works like Scene, only difference is that it is drawn over scene and handles mouse events by default

# Examples #

## Player ##
	
A player would be represented as an Actor  
Might have several Resources, such as: Skills, Location, Health  
Might have an animated sprite Agent
	
