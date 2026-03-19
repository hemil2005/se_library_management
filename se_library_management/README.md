# Library Management System - User Guide

## System Overview
This is a console-based Library Management System with three types of users:
- **Students**: Can reserve books and view their issued books
- **Teachers**: Can add books, issue books directly, and manage reservations
- **Admins**: Can manage users and oversee the entire system

## Sample Login Credentials
- Student: `S001` / `pass123`
- Student: `S002` / `pass456`
- Teacher: `T001` / `teach123`
- Teacher: `T002` / `teach456`
- Admin: `A001` / `admin123`

## Features by User Type

### Student Features:
1. **View Available Books** - Browse all books that can be reserved
2. **Create Reservation** - Reserve a book (valid for 3 days)
3. **View My Reservations** - See all active reservations with days remaining
4. **Cancel Reservation** - Cancel a reservation before it expires
5. **View My Issued Books** - See books currently borrowed
6. **Credit System** - Students start with 100 credits
   - Late returns deduct 5 credits per day

### Teacher Features:
1. **View Available Books** - Browse library collection
2. **Add New Book** - Add new books to the library
3. **Issue Book Directly** - Issue books without reservation (to students or self)
4. **View All Reservations** - See all pending reservations
5. **Approve/Issue Book from Reservation** - Fulfill student reservations
6. **Return Book** - Process book returns (for students or self)
   - Can apply late fees when processing student returns
7. **View My Issued Books** - See books currently borrowed

### Admin Features:
1. **View All Books** - Complete library catalog
2. **Add New Book** - Add books to the system
3. **View All Users** - See registered users
4. **Add New Student** - Register new students
5. **Add New Teacher** - Register new teachers
6. **View All Reservations** - Monitor all reservations

## Key System Features

### Reservation System:
- Students can reserve available books
- Reservations are valid for **3 days**
- After 3 days, reservations automatically expire
- Book copies are held during reservation period
- Students must visit library within 3 days to collect

### Credit System:
- All students start with **100 credits**
- Late returns: **-5 credits per day**
- Teachers process returns and apply late fees
- Low credits may affect future borrowing (can be extended)

### Book Management:
- Each book has total copies and available copies
- Books show availability status
- Teachers can add new books anytime
- System tracks issued vs available copies

## Sample Books in System:
1. Introduction to C++ (5 copies)
2. Data Structures and Algorithms (3 copies)
3. Operating Systems (4 copies)
4. Database Systems (2 copies)
5. Computer Networks (3 copies)

## Workflow Examples

### Student Reserving a Book:
1. Login as student
2. View Available Books
3. Create Reservation (enter book ID)
4. Visit library within 3 days
5. Teacher approves and issues book

### Teacher Issuing a Book:
1. Login as teacher
2. View All Reservations
3. When student arrives, approve reservation
4. Book is issued to student

### Returning a Book:
1. Teacher processes return
2. Enter student ID and book ID
3. Enter days late (if any)
4. Credits deducted if late
5. Book returned to available pool

## Technical Details

### Classes Structure:
- **User** (Base class)
  - Student (inherits User)
  - Teacher (inherits User)
  - Admin (inherits User)
- **Book** - Manages book information and copies
- **Reservation** - Handles 3-day reservations
- **LibrarySystem** - Central management system
- **Menu** - User interface handler

### Data Persistence:
Currently using in-memory storage. For next sessions:
- File I/O for saving data
- Load on startup, save on exit

## Next Enhancement Ideas:
1. File persistence (save/load data)
2. Search books by title/author
3. View borrowing history
4. Due date tracking for issued books
5. Email notifications (simulation)
6. Book categorization and filtering
7. Generate reports
8. Fine payment system
