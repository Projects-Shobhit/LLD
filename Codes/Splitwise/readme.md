# ABOUT
An expense sharing application is where you can add your expenses and split it among different people. The app keeps balances between people as in who owes how much to whom.

## Example

You live with 3 other friends.

You: User1 (id: u1)

Flatmates: User2 (u2), User3 (u3), User4 (u4)

---
### EXPENSE 1
This month's electricity bill was Rs. 1000.

Now you can just go to the app and add that you paid 1000,

select all the 4 people and then select split equally.

Input: u1 1000 4 u1 u2 u3 u4 EQUAL

For this transaction, everyone owes 250 to User1.

The app should update the balances in each of the profiles accordingly. User2 owes User1: 250 (0+250)

User3 owes User1: 250 (0+250)

User4 owes User1: 250 (0+250)

---
### EXPENSE 2
Now, It is the BBD sale on Flipkart and there is an offer on your card.

You buy a few stuffs for User2 and User3 as they asked you to.

The total amount for each person is different.

Input: u1 1250 2 u2 u3 EXACT 370 880

For this transaction, User2 owes 370 to User1 and User3 owes 880 to User1.

The app should update the balances in each of the profiles accordingly.

User2 owes User1: 620 (250+370)

User3 owes User1: 1130 (250+880)

User4 owes User1: 250 (250+0)

---
### EXPENSE 3

Now, you go out with your flatmates and take your brother/sister along with you.

User4 pays and everyone splits equally. You owe for 2 people.

Input: u4 1200 4 u1 u2 u3 u4 PERCENT 40 20 20 20

For this transaction, User1 owes 480 to User4, User2 owes 240 to User4 and User3 owes 240 to User4.

The app should update the balances in each of the profiles accordingly.

User1 owes User4: 230 (250-480)

User2 owes User1: 620 (620+0)

User2 owes User4: 240 (0+240)

User3 owes User1: 1130 (1130+0)

User3 owes User4: 240 (0+240)

## Requirements

**User**: Each user should have a userId, name, email, mobile number.

**Expense**: Could either be EQUAL, EXACT or PERCENT

Users can **add** any amount, **select** any type of expense and **split** with any of the available users.

The **percent** and **amount** provided could have **decimals** upto **two** decimal places.

In case of **percent**, you need to verify if the **total** **sum** of percentage shares is 100 or not.

In case of **exact**, you need to verify if the **total** **sum** of shares is equal to the total amount or not.

The application should have a capability to **show** **expenses** for a **single** **user** as well as balances for **everyone**.

When asked to show balances, the application should show balances of a user with **all** the users where there is a **non-zero balance.**

The amount should be **rounded** **off** to **two** decimal places. Say if User1 paid **100** and amount is split equally among 3 people. Assign **33.34** to first person and **33.33** to others.

## Input

You can create a few users in your main method. No need to take it as input.

There will be 3 types of input:

Expense in the format: ```<user-id-of-person-who-paid>``` ```<no-of-users>``` ```<space-separated-list-of-users>``` ```<EQUAL/EXACT/PERCENT>``` ```<space-separated-values-in-case-of-non-equal>```

Show balances for all: ```SHOW```

Show balances for a single user: ```SHOW <user-id>```

## Output

When asked to show balance for a single user. Show all the balances that user is part of:

Format: ```<user-id-of-x> owes <user-id-of-y>: <amount>```

If there are no balances for the input, print No balances

In cases where the user for which balance was asked for, owes money, they’ll be x. They’ll be y otherwise.

### ACTIVITY DIAGRAM

https://viewer.diagrams.net/?tags=%7B%7D&highlight=0000ff&layers=1&nav=1&title=ACTIVITYSPLITWISE.drawio#R7VxRe6I4FP01fvvUfkCA4mO1tp3dTttZ7HRmX%2FaLEpUdJDTEUefXbwJBhKClrRrbwYcKNyHEe3JuTi6hLdCdLq4IjCafsYeClqF5ixa4aBmGcQZ09sUty9SiA91JLWPie8KWG1z%2FFxJGTVhnvofiQkWKcUD9qGgc4jBEQ1qwQULwvFhthIPiXSM4FnfUcoM7hAGSqj36Hp2kVsc4y%2B3XyB9PsjvrdjstmcKssmg4nkAPz9dMoNcCXYIxTY%2Bmiy4KuPcyvzx%2BWj4GNz%2Fsqz%2B%2FxE%2FwofNX%2F%2FbrSdrY5UsuWf0EgkL66qap6dmDi3%2BHlKDPjvu1%2F%2FedTk4EljFdZv5CHnOfOMWETvAYhzDo5dYOwbPQQ7xVjZ3ldW4wjphRZ8b%2FEKVLMRbgjGJmmtBpIErZryDLb%2Fz6Uys7%2FS6aS04uFoWzpThL%2B8o7WIL2Gb%2BIejGekSHaUk8MCQrJGNEtTjtbgc9og%2FAUsU6y6wgKIPV%2FFjsHxfAdr%2BrlELEDgdILBoPo5E8YzMSdeiFFhJluZ9NBcoBH7M9DjEgsoZtjx4GYT3yK3AgmXpmzAFDEaYRDKkDU2Q%2FujAMYxwKLmBL8Y8UoXntFjxyqusj8RISixZrfZOdmpbYgYxaOMnLOc26vbJM1Xpva2%2FGoHAzMM78nhTZTowaFdK0a5p1zaFsvKzh0gSj0gziZaPg5gsMJ%2B5rFvFQplySO1EWtNpcMTTmXzhoulTlSh0y2SjJl3axg05cZSjpS4BJaRCiM0cenk6OcTkBCRuZXEDAljoreZf6KeHnMhh51KaS8fOQHQRcHDEp%2BIdCSz8rdayWjkSjxfMIUvY9D3hSecSfszfuGZhW8b8nOBxW%2BB3vzvfm879c8zh3is0XLeeCPubsGmFI8TUKOd85XQTz8Md6kFjHyna3eL8bFHQe554MXeFk0XA9ym3XvG2KcuPQe%2B6w7%2BbAxisNGLw%2BItF%2FiqtKYWHXj9cNktbZ8FzNecnaPiM9%2BNiKHmgbtutNgW%2Bk0aEuEd1HAMxqG1vt237t1e%2Byov4w%2B%2FswHbNUzn2G%2BJ1rtnUHtmgxK5yhVDMpCsSrQCpDlCB5VLKyN5H6mS2AWmW46h50us9%2B%2Fvtb48nB%2BIw2cYiQ0quXtdDHmSe%2FTUYDnwwmTuqceGvpxIlgrw3BJAkO2YjYsEZMLEox%2FqsSZfSnE2d5CsVMCyJRDsVMRics47ozUQHGG%2BWWk3jd%2Fs0XAs%2FwFO%2BEvWznA5VqFiPMy3qaGi6PnTNNKAyBtcbcS2JA5LfIH51FEcER8vgAtZxOqef%2FRpJSlXkq1GylVnlfrTMCOSikF3pWUOhrQgKlU%2F1Y8lvh23u034maT%2BlQubprYKIW8Q4ibt9HMafRGTinj2PRGloBdT5xbne89t2VdSO5n3qBFH0ORQB%2BiBFM5sz71PS%2FlIYr9X3CQNMVdLMQxa9fq8Huxthj1YoGXFPBCHKJS1BSmfWFVVudWxd4H65DPOLK9YUWobu8apEoq3qx4GnVYpOQ1VkOqIyVVxUPbBqrE5c6RQZXNgYrk3%2BrkOFZZwDyU%2FHtVbstyFOS2gLwL4PfVmlYp1Jrqtab8zLYRMIWV9bEIGNNQGmrfwz4JUDfLZW7A%2FkCpyc2bb4tB0L2%2Be2x90B0T5WW3rXyvoNnsmJAoUodLQCWXTFstaMclQOuDZikFrSJrYtgBFZGqAKf9NMNZwUmqD85ZBSdaJP7MitnRmBYsInimX2vVgvT7Mr1TdlXzfCGNyiXV41S8EHHQ5wtWo3qeJT2oS3qlu0NNOavjTpjMYLdKLuYvGP3BXzsawACGQ6T6zb39S5628tWfpUtOPuL0jRp2WYdi105yOno2gPaa1MmcInM5jtgUOPKHFYT%2BcHwuZ3Mc5W%2FimvLKssmcp7G3xJN2hbA5bDpHfgbfJN6qEm%2BOrhip7GbKJKhR0KCrQlVrzLob8BVt4NW2T4jPXuBo2%2BsDa2v9%2FUy4luLdjO9hGVR3XFpKtzhm3XxD7kM3NiQ%2FuqyeH7JmmyzHdjFQmmJ0rSL5fNg0R7PlYdPuFKsGVofVA%2FITbbd%2Fd78rdjEAp34IKXduJb%2F2xoqyp42KzcX2npYzbgdFt%2Fri6fskvuw8WNE%2FV%2FTpRN4H2SUIUjalGVqH99y9vutcf%2Bqzo6uH%2Bz6LjTaccheFgzhay%2FYOSJ2wCsCGsHpB4PzUx%2B%2BDh8k6WfSxtG4GYJ%2ByvZyIaMuDx2xXjJ72y0cPO83%2F51wqsfJ%2F3Qd6%2FwM%3D




