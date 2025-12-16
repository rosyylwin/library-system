# Assignment Source Code
Author: Rosy Lwin
Student ID: 107198631

This project implements a complete Library Management System.

Features:
User Management
    Supports three user types: Student, Teacher, Other.
    You can :
        - Add users
        - Remove ssers
        - Search users
        - Display all users
        - Track outstanding fees
Book Mangement
    You can:
        - Add books
        - Remove books
        - Search books
        - Display all books
        - Track total + available copies
    Books are stores compactly and safely.
Borrow/Return System
    The system maintains full BorrowRecord logs:
        - Borrow date
        - Due date
        - Return date
        - Late fee calculation
        - Returned or not returned status
    Borrowing decreases available copies. Returning increases them.
Late Fees
    Late days are automatically calculated and applied to the user's account.
Reports
    You can view:
        - Total number of books
        - Total number or users
        - Total number of currently borrowed books
        - Available copies for any given ISBN

Project Status:
    Project runs, all functions work except the display functions (9 - 12).

Compilation Instuctions:
    Type : g++ src/Book.cpp src/BorrowRecord.cpp src/Library.cpp src/User.cpp src/main.cpp -o library
    To run type : ./library

User Manual:
    When running the system, the following menu is displayed:
    1. Add Book
    2. Remove Book
    3. Search Book
    4. Add User
    5. Remove User
    6. Search User
    7. Borrow Book
    8. Return Book
    9. Display All Books
    10. Display All Users
    11. Display All Records
    12. Show Report
    13. Save and Exit
Adding a Book
    You will be prompted for:
        - ISBN
        - Title
        - Author
        - Year
        - Total Copies
Adding a User
    Choose user type:
        1. Student
        2. Teacher
        3. Other
Borrowing a Book
    Inputs required:
        - User ID
        - ISBN
        - Borrow date(YYYY MM DD)
        - Due date (YYYY MM DD)
    Creates a BorrowRecord, updates book availabilty.
Returning a Book
    Inputs required:
        - Record ID
        - Return date (Y M D)
        - Late fee per day
    Late fees automatically charge the user.

UML diagram:
''' mermaid
[![](https://mermaid.ink/img/pako:eNqtV1tP2zAU_iuReSlgUC_Q0movQDUJCZgEbBITL25tWo8krmyHLbDy2-dbWjtxQNrWhzQ537l88Tk-x3kFc4YJmIB5ioSYUrTgKHvIE_UzkuSMsafk1Ur070BITvNFQsUsb0ollSlpilEhl4x78iIXdJETnNBcJiVBrdicrSgRd0yi9H2V02dEUzTT0beK-5p9Z7cu0Nyh5QodN2hYQD-eb7Yg8uL27Lqzm9g3CqE77akFOzXuW8B7FVNBhXqNEDjf0ngH37xzU0dUrORuKHV8UE1smJS-EGFso3RyXzxjnLOfX3Idc8aYl5V9TmTB8ygkCKcopS_k_PZbbC0wCTRSmpNdU3q-DhWrFJUdJhyftf2z16_KQfLp98FBcisLTKrF2IrvCJovCfdr24Bebe9UtY2bshxlXmHvaNO7ckUSqS6eHLNC5SN5JERMi7AWtUlQi0ZAMTS-ofFUr7lpS-FcK4sWqGKm4Oo2VPhsuSnckg1zrtEOyoKyWaEyJm4k5O9TrZnubbLq58hlM9aCMvRDNxXPt1P2FtXo_BPpGh9XRjE-mKwQl5mpPc-3s_BIbRX_J7MzszNvyJxxHKPHDXIxbSKFChKT13q8brZ2-xN8H_ZsH7piuVy2YFNU1hBckIgvJY25UeLQg24zie07BNeUrTji3AIx_xYxIYKZsV3Y2jDxAA4LSOGshLMMzjDEJcQZxLi2o29cEt7ZvK1g2wSi4satQLPxZog_bdASKkZByaFSXCKpe0F9fLiq-2AHbzr1diE-6Nh-xV7SGUe8DIr1mcwl42-697_pl3kSTdB0izdTtiJmuiXz5qpeBAl1cTu1cWfOBvoSmWwZeyabs0NkvCE-X3q4vt0LvZtub5i3uHfjoMX5BvVapTeQTWy7j6E53jQLMT6ujWHVGiAvIc8gx1ANsIaBPunoE4k2EY2SqVDNL4qeuR5wzgrVoiMKm-OMO3fYpQzVXEmdphWLKOY4RDFbGCGaMoStv0eaNl9cIJv8Flhb24it1u_A2rri1GrfprAGECw4xWAieUEgyAjPkH4EZk89ALkk6twCJuoWk0dUpPIBPOTabIXy74xllSVnxWIJJo8oFeqpWGHVFtznwEaF5Jhwkz4w6ffGR8YJmLyCX2BycNI_HAx7o-Nxt388HB91hxCUYHI8OhyM1eOg3z8Zj476veEaghcTt3c4GB11--NBt3sy7I2HIwgIpmoHX7kvEv23_gNpwMnJ?type=png)](https://mermaid.live/edit#pako:eNqtV1tP2zAU_iuReSlgUC_Q0movQDUJCZgEbBITL25tWo8krmyHLbDy2-dbWjtxQNrWhzQ537l88Tk-x3kFc4YJmIB5ioSYUrTgKHvIE_UzkuSMsafk1Ur070BITvNFQsUsb0ollSlpilEhl4x78iIXdJETnNBcJiVBrdicrSgRd0yi9H2V02dEUzTT0beK-5p9Z7cu0Nyh5QodN2hYQD-eb7Yg8uL27Lqzm9g3CqE77akFOzXuW8B7FVNBhXqNEDjf0ngH37xzU0dUrORuKHV8UE1smJS-EGFso3RyXzxjnLOfX3Idc8aYl5V9TmTB8ygkCKcopS_k_PZbbC0wCTRSmpNdU3q-DhWrFJUdJhyftf2z16_KQfLp98FBcisLTKrF2IrvCJovCfdr24Bebe9UtY2bshxlXmHvaNO7ckUSqS6eHLNC5SN5JERMi7AWtUlQi0ZAMTS-ofFUr7lpS-FcK4sWqGKm4Oo2VPhsuSnckg1zrtEOyoKyWaEyJm4k5O9TrZnubbLq58hlM9aCMvRDNxXPt1P2FtXo_BPpGh9XRjE-mKwQl5mpPc-3s_BIbRX_J7MzszNvyJxxHKPHDXIxbSKFChKT13q8brZ2-xN8H_ZsH7piuVy2YFNU1hBckIgvJY25UeLQg24zie07BNeUrTji3AIx_xYxIYKZsV3Y2jDxAA4LSOGshLMMzjDEJcQZxLi2o29cEt7ZvK1g2wSi4satQLPxZog_bdASKkZByaFSXCKpe0F9fLiq-2AHbzr1diE-6Nh-xV7SGUe8DIr1mcwl42-697_pl3kSTdB0izdTtiJmuiXz5qpeBAl1cTu1cWfOBvoSmWwZeyabs0NkvCE-X3q4vt0LvZtub5i3uHfjoMX5BvVapTeQTWy7j6E53jQLMT6ujWHVGiAvIc8gx1ANsIaBPunoE4k2EY2SqVDNL4qeuR5wzgrVoiMKm-OMO3fYpQzVXEmdphWLKOY4RDFbGCGaMoStv0eaNl9cIJv8Flhb24it1u_A2rri1GrfprAGECw4xWAieUEgyAjPkH4EZk89ALkk6twCJuoWk0dUpPIBPOTabIXy74xllSVnxWIJJo8oFeqpWGHVFtznwEaF5Jhwkz4w6ffGR8YJmLyCX2BycNI_HAx7o-Nxt388HB91hxCUYHI8OhyM1eOg3z8Zj476veEaghcTt3c4GB11--NBt3sy7I2HIwgIpmoHX7kvEv23_gNpwMnJ)
'''
