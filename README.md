# Reflection

This is the repository for my youtube tutorials on Reflection:
https://www.youtube.com/playlist?list=PL-wfxf45KxnRWBmzmuQ8I9Hsq6KbqW6UB

This tutorial covers how to make a header only simple reflections system that is fully customizable.

## Tutorial 1 - TypeId

This video covered the basics on making type information available to any place inside of the project before the main function gets accessed.

## Tutorial 2 - Variables

In this video we created the VariableId class that is capable of describing a class and its possible modifiers, like const, volatile, \*, &, &&, [].

## Tutorial 3 - Member Variables

In this video we created a structure for holding Member Variable information and storing it in a static hash map. Using this we can query and modify each variable that is contained inside a user defined type.

## Example 1 - Serialization

In this example we go over a serialization system that uses the Member Variables Reflection System to query information about an instance of a type and serializes it into either json or binary.
