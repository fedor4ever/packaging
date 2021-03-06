// STRING FUNCTIONS


/**
 * Get relative URL.
 *
 * @param url URL string
 * @return relative part of the URL
 * @type String
 */ 
function getRelativeUrl(url) {
    var i = url.lastIndexOf("/");
    if (i != -1) {
        return url.substring(i + 1);
    } else {
        return url;
    }
}

/**
 * Get string value for array where list is in prose.
 *
 * @param array array to get the string value for
 * @type String
 * @return array string value in prose
 */
function toProseString(array) {
	switch (array.length) {
	case 0:
		return "";
		break;
	case 1:
		return array[0];
		break;
	case 2:
		return array[0] + " and " + array[1];
		break;
	default:
		var t = "";
		for (var i = 0; i < array.length - 1; i++) {
			t += array[i] + ", ";
		}
		return t + "and " + array[array.length - 1];
	}
}


// EVENT FUNCTIONS


/**
 * Return target node of an event.
 *
 * @return target node of the event
 * @type Node
 **/
function getTargetNode(event) {
	if (event.target) {
		return event.target;
	} else if (event.srcElement) {
		return event.srcElement;	
	} else {
		return null;	
	}
}

/**
 * Attach event listener to a DOM node.
 *
 * @param node DOM node to attach lister to
 * @param type Type of event to catch
 * @param func Function to act as the handler 
 */
function attachEventListener(node, type, func) {
    if (node.addEventListener) {
        node.addEventListener(type, func, false);
    } else if (node.attachEvent) {
        node.attachEvent("on" + type, function() { func.call(this, event); } );
    }
}


// CSS CLASS FUNCTIONS


/**
 * Switch class of an element.
 *
 * @param n Element node to change the class of
 * @param f Class to change from
 * @param t Class to change to
 * @param arr Class array (optional)
 */
function switchClass(n, f, t, arr) {
    if (arr == undefined) {
        arr = getClassArray(n.className);
    }
    for (var i = 0; i < arr.length; i++) {
        if (arr[i] == f) {
            arr[i] = t;
        } else if (arr[i] == t) {
            arr[i] = f;
        }
    }
    n.className = arr.join(" "); 
}

/**
 * Test if element is of class.
 *
 * @param n Element node to test
 * @param c Class to test for
 * @param arr Class array (optional)
 * @return boolean value if element is of the tested class
 */
function isClass(n, c, arr) {
    if (arr == undefined) {
        arr = getClassArray(n.className);
    }
    for (var i = 0; i < arr.length; i++) {
        if (arr[i] == c) {
            return true;
        }
    }
    return false;
}

/**
 * Add class to an element.
 *
 * @param n Element node to add the class to
 * @param c Class to add
 * @param arr Class array (optional)
 */
function addClass(n, c, arr) {
    if (arr == undefined) {
        arr = getClassArray(n.className);
    }
    if (!isClass(n, c, arr)) {
        n.className = n.className + " " + c;
    }
}

/**
 * Remove class
 *
 * @param n Element node to remove the class from
 * @param c Class to remove
 * @param arr Class array (optional)
 */
function removeClass(n, c, arr) {
    if (arr == undefined) {
        arr = getClassArray(n.className);
    }
    if (isClass(n, c, arr)) {
        var ret = new Array();
        for (var i = 0; i < arr.length; i++) {
            if (arr[i] != c) {
                ret.push(arr[i]);
            }
        }
        n.className = ret.join(" ");
    }
}

/**
 * Get class names as an array
 *
 * @param c class name
 * @return array of class members
 * @type Array
 */
function getClassArray(c) {
    return new String(c).split(" ");
}


// COLLECTION CLASSES


/**
 * Multi value Map.
 *
 * Usage:
 *
 * >> var m = new Map();
 * >> m.put("a", "first");
 * >> m.put("a", "second");
 * >> m.size();
 * 1
 * >> m.get("a");
 * ["first", "second"]
 *
 * @constructor
 * @param {Boolean} multi Boolean to define whether map will store dublicate values into an array
 */
function Map(multi) {
    this.keys = new Array();
    this.values = new Array();
    this.multi = (multi == undefined ? false : multi); 
}
Map.prototype.toString = function() {
    var val = "[Object Map";
    if (this.keys.length != 0) {
        val += ": {";
        for (var i = 0; i < this.keys.length; i++) {
        	if (i != 0) {
        		val += "; ";
        	}
        	val += this.keys[i] + ":";
	        for (var j = 0; j < this.values[i].length; j++) {
	        	if (j != 0) {
	        		val += ",";
	        	}
	        	val += " " + this.values[i][j].toString();
	        }
	       
        }
        val += "}";
    }
    val += "]";
    return val;
}
/**
 * @param {String} key
 * @param {Object} value
 */
Map.prototype.put = function(key, value) {
    var index = this._find(key);
    var a;
    if (index != -1 ) {
        a = this.values[index];   
    } else {
        index = this.keys.length;
        this.keys[index] = key;
        a = new Array();
    }
    if (this.multi) {
        a[a.length] = value;
    } else {
        a[0] = value;
    }
    this.values[index] = a;
}
/**
 * @param {String} key
 * @type Object
 */
Map.prototype.get = function(key) {
    var index = this._find(key);
    if (index != -1) {
        if (this.multi) {
            return this.values[index];
        } else {
            return this.values[index][0];
        }   
    } else {
        return null;
    }
}
/**
 * Iterator for the value set.
 *
 * @return Iterator for the values
 * @type ArrayIterator
 */
Map.prototype.iterator = function(key) {
    var index = this._find(key);
    var val;
    if (index != -1) {
        val = this.values[index];
    } else {
        val = [];
    }
    return new ArrayIterator(val);
}
/**
 * @type Number
 */
Map.prototype.size = function() {
	return this.keys.length;
}
/**
 * @param {String} key
 * @type Number
 */
Map.prototype._find = function(key) {
    var index = -1;
    for (var i = 0; i < this.keys.length; i++) {
        if (this.keys[i] == key) {
            index = i;
            break;
        }
    }
    return index;
}

/**
 * Map.
 *
 * Usage:
 *
 * >> var m = new SingleValueMap();
 * >> m.put("a", "first");
 * >> m.put("a", "second");
 * >> m.size();
 * 1
 * >> m.get("a");
 * "second"
 *
 * @constructor
 */
function SingleValueMap() {
    this.keys = new Array();
    this.values = new Array();
    this.multi = false; 
}
SingleValueMap.prototype = new Map(false);
SingleValueMap.prototype.toString = function() {
    return "[Object SingleValueMap]";
}

/**
 * Set.
 *
 * @constructor
 */
function Set() {
	this.keys = new Array();
}
Set.prototype.toString = function() {
	var val = "[object Set";
	if (this.keys.length > 0) {
		val += ":";
		for (var i = 0; i < this.keys.length; i++) {
			if (i != 0) {
				val += ",";
			}
			val += " " + this.keys[i];
		}
	}
	val += "]";
	return val;
}
Set.prototype.add = function(value) {
	var i = this.m_find(value);
	if (i == -1) {
		this.keys[this.keys.length] = value;
	}
}
Set.prototype.iterator = function() {
	return new ArrayIterator(this.keys)
}
Set.prototype.size = Map.prototype.size;
Set.prototype.m_find = Map.prototype._find;

/**
 * Array Iterator
 *
 * Usage:
 *
 * >> var arr = new Array("a", "b", "c");
 * >> for (var itr = new ArrayIterator(arr); itr.hasNext();) {
 * >>    alert(itr.next());
 * >> }
 * "a"
 * "b"
 * "c"
 *
 * @constructor
 * @param {Array} arrayLike array to iterate through
 */
function ArrayIterator(arrayLike) {
    this.arrayLike = arrayLike;
    this.i = 0;
    NoSuchElementException = function() {};
    NoSuchElementException.prototype = new Error();
    NoSuchElementException.prototype.name = 'NoSuchElementException';
    NoSuchElementException.prototype.message = 'Iteration has no more elements';
}
/**
 * String value of the object.
 *
 * @type String
 */
ArrayIterator.prototype.toString = function() {
  return "[Object ArrayIterator]";
}
/**
 * @type Object
 */
ArrayIterator.prototype.next = function() {
    if (!this.hasNext()) {
        throw new NoSuchElementException();
    }
    if (this.arrayLike.item) {
    	return this.arrayLike.item(this.i++);
    } else {
    	return this.arrayLike[this.i++];
    }
}
/*/
 * @type Boolean
 */
ArrayIterator.prototype.hasNext = function() {
    return this.i < this.arrayLike.length;
}


// DOM FUNCTIONS


/**
 * Get next sibling by element name
 *
 * @param n current element
 * @param t element name of the desired sibling
 * @return next sibling element with a given name or null if not found
 * @type Element
 */
function getNextSiblingByTagName(n, t) {
    if (n != null) {
        var tag = t.toLowerCase();
    	var i = n;
    	while (true) {
    		if (i.nodeType == 1 && i.nodeName.toLowerCase() == tag) {
    		    return i;
    		}
    		if (i.nextSibling != null) {
    			i = i.nextSibling;
    		} else {
    			return null;
    		}
    	}
	}
	return null;
}

/**
 * Get child element by element name
 *
 * @param node parent element
 * @param name element name of the desired child elements
 * @return array of child elements
 * @type Array
 */
function getChildElementsByTagName(node, name) {
	var buf = new Array();
	var tag = undefined;
    if (name != undefined) {
        tag = name.toLowerCase();
    }
	for (var n = node.firstChild; n != null; n = n.nextSibling) {
		if (n.nodeType == 1 && (name == undefined || n.nodeName.toLowerCase() == tag)) {
			buf[buf.length] = n;
		}
	}
	return buf;
}

/**
 * Wrap child nodes of an element to wrapper element.
 *
 * @param parent element whose child nodes to wrapper
 * @param wrapper wrapper element 
 */
function wrapChildElements(parent, wrapper) {
	for (var c = parent.firstChild, n = null; c != null; c = parent.firstChild) {
		n = parent.removeChild(c);
		wrapper.appendChild(n);
	}
	parent.appendChild(wrapper);
}

/**
 * Get elements by class name.
 *
 * @param node DOM node whose descendants select
 * @param cls class name
 * @param elem element name (optional)
 * @return array of DOM nodes
 * @type Array
 */
function getElementsByClassName(node, cls, elem) {
	if (elem == undefined) {
		elem = "*"
	}
	var res = new Array();
	for (var el = document.getElementsByTagName(elem), i = 0; i < el.length; i++) {
	  	if (isClass(el[i], cls)) {
	    	res[res.length] = el[i];
		}
	}
	return res;
}


// FORM FUNCTIONS


/**
 * Validate form
 *
 * @param form form to validate
 * @type Boolean
 * @return boolean value whether validation was successful
 */
function validateForm(form) {
	var isValid = true;
	var missing;
    var col = form.elements;
    for (var i = 0, labels, r = new Array(); i < col.length; i++) {
        if (isClass(col[i], "required") && !col[i].disabled) {
            var f = col[col[i].name];
            var valid = false;
            if (f.length == undefined) {
                if (f.value != "") {
                    valid = true;
                }
            } else {
                if (col[i].value != f[0].value) {
                    continue;
                }
                for (var j = 0; j < f.length; j++) {
                    if (f[j].checked & f[j].className.indexOf("nonrequired") == -1) {
                        valid = true;
                        break;
                    }
                }
            }
            if (labels == undefined) {
            	labels = form.getElementsByTagName("label");
            }
			var label;
            for (var j = 0; j < labels.length; j++) {
                if (labels[j].htmlFor == col[i].name) {
                	label = labels[j];
                }
            }
            if (!valid) {
            	isValid = false;
                if (missing == undefined) {
                	missing = new Array();
                }
                missing[missing.length] = label.firstChild.data;
                addClass(label, "form_invalid");
            } else {
            	removeClass(label, "form_invalid");
            }
        }
    }
 	if (!isValid) {
	    window.alert("Required field" + (missing.length < 2 ? "" : "s")
	    	+  " " + toProseString(missing)
	    	+ " " + (missing.length < 2 ? "has" : "have") + " no value");
    }
    return isValid;
}