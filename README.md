# Cinema Reservation System

## Software Requirements Specification (SRS)

### 1. Introduction

#### Cinema Management & Ticket Booking System

Small and medium-sized cinema chains often struggle with managing movie schedules, ticket bookings, and hall availability when relying on manual methods such as paper records or basic spreadsheets. These traditional approaches make it difficult to avoid seat conflicts, track movie showtimes accurately, and generate reliable sales reports across multiple cinema branches.

The **Cinema Management & Ticket Booking System** provides a lightweight, console-based digital solution developed using Bash scripting and Linux command-line utilities, following structured programming concepts and modular script design.

This system simplifies cinema operations by automating movie scheduling, seat reservations, and ticket management, while ensuring data consistency and minimizing human errors—without requiring complex graphical interfaces or heavy infrastructure.

#### 1.2 Scope

The Cinema Reservation System is a console application that provides:

- User authentication and authorization for three user roles (customers, employee, admin)
- Movie browsing and searching capabilities
- Reservation management for customers
- Administrative functions for movie management

#### 1.3 Definitions, Acronyms, and Abbreviations

- **SRS** — Software Requirements Specification
- **CRUD** — Create, Read, Update, Delete
- **Admin** — Administrator/Manager
- **User** — Any person with an account on the system
- **Employee** — Any person working in the company except manager

#### 1.4 References

- https://medium.com/@abdul.rehman_84899/ieee-standard-for-software-requirements-specifications-ieee-830-1998-0395f1da639a
- IEEE Standard for Software Requirements Specifications (IEEE 830–1998)

### 2. Overall Description

#### 2.1 Product Perspective

The Cinema Reservation System is a standalone console application that manages movie listings, schedules, and customer reservations for a cinema.

#### 2.2 Product Functions

- User registration and authentication
- Movie browsing and searching
- Reservation creation and management
- Administrative movie management

#### 2.3 User Classes and Characteristics

| User Type   | Description                                      | Privileges                                                                 |
|-------------|--------------------------------------------------|----------------------------------------------------------------------------|
| Customer    | General users who want to watch movies            | Browse movies, make reservations, manage own account                        |
| Employee    | Cinema staff members                             | View schedules, assist with reservations, view movie information           |
| Manager (Admin) | System administrators                        | Full CRUD on movies, set schedules, manage all system functions            |

#### 2.4 Operating Environment

- Console application
- Linux file system will be used as the database

#### 2.5 Design and Implementation Constraints

- All users must have an account to access system functionalities
- System must support concurrent users

#### 2.6 Assumptions and Dependencies

- Users have valid email addresses for registration

### 3. System Features and Requirements

#### 3.1 User Authentication and Authorization

**Description**  
All users must create an account and authenticate to access system features.

**Functional Requirements**

| ID     | Requirement                                                      |
|--------|------------------------------------------------------------------|
| FR-1.1 | System shall allow new users to register with email and password |
| FR-1.2 | System shall authenticate users via login credentials            |
| FR-1.3 | System shall support three user roles: Customer, Employee, Manager |
| FR-1.4 | System shall restrict features based on user role                |
| FR-1.5 | System shall allow users to logout securely                       |

#### 3.2 Movie Management (Admin Only)

**Description**  
Administrators can perform CRUD operations on movies and set schedules.

**Functional Requirements**

| ID     | Requirement                                             |
|--------|---------------------------------------------------------|
| FR-2.1 | Admin shall be able to CREATE new movie entries         |
| FR-2.2 | Admin shall be able to READ all movie information       |
| FR-2.3 | Admin shall be able to UPDATE existing movie details    |
| FR-2.4 | Admin shall be able to DELETE movies from the system    |
| FR-2.5 | Admin shall be able to set showtimes for upcoming movies |
| FR-2.6 | Admin shall be able to modify existing showtimes        |

#### 3.3 Movie Browsing and Search (All Users)

**Description**  
Users can browse available movies and search/filter by various criteria.

**Functional Requirements**

| ID     | Requirement                                             |
|--------|---------------------------------------------------------|
| FR-3.1 | System shall display all available movies               |
| FR-3.2 | Allow sorting movies by genre                           |
| FR-3.3 | Allow sorting movies by rating                          |
| FR-3.4 | Allow searching movies by title                         |
| FR-3.5 | Allow searching movies by author                        |
| FR-3.6 | Allow searching movies by genre                         |
| FR-3.7 | Allow searching movies by rating                        |
| FR-3.8 | Display movie details including showtimes               |

#### 3.4 Reservation System (Customer)

**Description**  
Customers can make and manage reservations for movie showings.

**Functional Requirements**

| ID     | Requirement                                                            |
|--------|------------------------------------------------------------------------|
| FR-4.1 | Customer shall be able to select a movie and showtime                   |
| FR-4.2 | Customer shall be able to create a reservation                          |
| FR-4.3 | Customer shall be able to view their existing reservations             |
| FR-4.4 | Customer shall be able to cancel a reservation                         |
| FR-4.5 | System shall confirm reservation with a confirmation number            |
| FR-4.6 | System shall prevent double-booking of seats (if applicable)           |

**Reservation Entity Attributes**

| Attribute      | Data Type | Description                              |
|----------------|-----------|------------------------------------------|
| reservation_id | Integer   | Unique identifier                        |
| customer_id    | Integer   | Reference to customer                    |
| movie_id       | Integer   | Reference to movie                       |
| showtime       | DateTime  | Selected showtime                        |
| num_tickets    | Integer   | Number of tickets reserved               |
| status         | Enum      | Active/Cancelled                         |
| created_at     | DateTime  | Timestamp of creation                    |

#### 3.5 Employee Functions

**Description**  
Employees can access movie information and assist with operations.

**Functional Requirements**

| ID     | Requirement                                      |
|--------|--------------------------------------------------|
| FR-5.1 | Employee shall be able to view all movie listings|
| FR-5.2 | Employee shall be able to view movie schedules   |
| FR-5.3 | Employee shall be able to view reservation details |

### 5. Non-Functional Requirements

#### 5.1 Performance Requirements

| ID       | Requirement                                          |
|----------|------------------------------------------------------|
| NFR-1.1  | System shall load pages within 3 seconds             |
| NFR-1.2  | System shall support at least 100 concurrent users   |
| NFR-1.3  | Search results shall be returned within 2 seconds    |

#### 5.2 Security Requirements

| ID       | Requirement                                                  |
|----------|--------------------------------------------------------------|
| NFR-2.1  | Passwords shall be encrypted/hashed before storage           |
| NFR-2.2  | User sessions shall timeout after 30 minutes of inactivity   |
| NFR-2.3  | Role-based access control shall be enforced                  |
| NFR-2.4  | All data transmission shall be encrypted via HTTPS           |

#### 5.3 Availability Requirements

| ID       | Requirement                            |
|----------|----------------------------------------|
| NFR-3.1  | System shall be available 24/7 for customers |
| NFR-3.2  | System uptime shall be 99% or higher   |

#### 5.4 Usability Requirements

| ID       | Requirement                                      |
|----------|--------------------------------------------------|
| NFR-4.1  | Interface shall be intuitive and user-friendly   |
| NFR-4.2  | System shall be accessible on desktop and mobile browsers |
| NFR-4.3  | Error messages shall be clear and helpful        |

#### 5.5 Maintainability Requirements

| ID       | Requirement                                      |
|----------|--------------------------------------------------|
| NFR-5.1  | Code shall be modular and well-documented        |
| NFR-5.2  | System shall support easy updates and patches    |

### User Stories

- **As a customer**,  
  I am very passionate about movies and cinema, and I face many problems during my journey to watch new movies in cinemas.  
  I want a smart and comfortable way to browse, register, and book movies,  
  so that I can enjoy watching new films easily without inconvenience.

- **As a manager**,  
  I want to have centralized access to monitor and manage all my cinemas from one place,  
  so that I can save time, reduce costs, and manage operations efficiently.

- **As an employee**,  
  I want to perform my tasks faster and more easily,  
  so that I can handle a large number of customers efficiently and reduce delays during daily operations.