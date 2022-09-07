# ofxRTTrP

OpenFrameworks addon used to retrieve data from [Real-Time Tracking Procol](https://rttrp.github.io/RTTrP-Wiki/index.html). This is the protocol used by [Blacktrax](https://Blacktrax.cast-soft.com/).

For now it works only in main thread, but i think it is possible a multithread implementation  with a marked improvement in performance.



## Compatibility

Tested with OpenFrameworks 0.9.8 with Mac OSX 10.14.1. Shoud be compatible also with Windows 10.

## Requirements
- ofxNetwork

## Examples
See the examples:
- example-main-thread

### Example-main-thread
1) Bind an input UDP port (using ofxNetwork)
2) parse messages and stored the first trackable
3) draw an ellipse with with the orders received
