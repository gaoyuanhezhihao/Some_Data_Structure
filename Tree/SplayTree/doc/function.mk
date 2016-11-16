---
title: "Splaying tree"
output: html_document
---

splaying tree core functions 

```
tree::insert():
	if root is null:
		create root
	else:
		root <- root insert new node
```
```{python}
node::find():
	IN:target
	OUT: new root of this subtree, deep count
	if target > this.element:
		return find_in_right()
	else if target < this.element:
		return find_in_left()
	else:
		# this is the node to find:
		deep count <-- 1
		return this, deep count
```

```{python}
node::find_in_right()
	IN:target
	OUT: root of this subtree, deep count
	------
	root of sub tree <-- this
	this.right <-- right.find
	if deep count == 2:
		root of sub tree <-- Make Rotation
		deep count = 1
	else:
		deep count <-- deep count + 1
	return root of sub tree, deep count
```

```{python}
node::find_in_left()
	IN:target
	OUT: root of this subtree, deep count
	------
	root of sub tree <-- this
	this.left <-- left.find
	if deep count == 2:
		root of sub tree <-- Make Rotation
		deep count = 1
	else:
		deep count <-- deep count + 1
	return root of sub tree, deep count
```
```{python}
node::rotate_r()
	IN: target of the findation
	OUT: root of this subtree after rotation.
	------
	get child handler
	if zigzig mode:
		get grand child handler
		swap
	else: # zigzagmode
		get grand child handler
		swap
	return grand child handler
```
```{python}
node::rotate_l()
	IN: target of the findation
	OUT: root of this subtree after rotation.
	------
	get child handler
	if zigzig mode:
		get grand child handler
		swap
	else: # zigzagmode
		get grand child handler
		swap
	return grand child handler
```
```{python}
node::find_root()
	IN: target to find.
	OUT:
	------
	if data < target:
		right <-- right.find
		if deep count is 2:
			rotate right
		else:
			rotate with child
	else if target < data:
		left <-- left.find
		if deep count is 2:
			rotate left
		else:
			rotate with child
	else:
		return this
```