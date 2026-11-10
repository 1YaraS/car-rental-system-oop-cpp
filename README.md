# Car Rental Agency Management System (C++ OOP)

## Overview
A comprehensive console-based Car Rental Management System developed in modern C++ demonstrating advanced Object-Oriented Programming (OOP) concepts. The system handles fleet inventory, customer and employee records, rental transactions, and automated invoicing.

---

## OOP Architecture & Design Patterns

* Single Inheritance: Client class inherits core personal attributes (`name`, surname, age`) from base class `Person.
* Multiple Inheritance: Employee inherits simultaneously from both Person (personal identity) and Worker (operational role & base salary).
* Operator Overloading:
  * operator==: Compares two Car instances using vehicle license plates.
  * operator<: Evaluates daily rental prices to identify economical options.
* Composition & Aggregation: The centralized Agency class coordinates internal arrays for Car, Client, and Employee objects.
* Pass-by-Reference: Critical methods like processRental pass references (`Car &car`) to directly modify vehicle availability state upon checkout.

---

## Class Hierarchy

```text
       Person           Worker
       /    \            /
      /      \          /
  Client     Employee (Multiple Inheritance)
