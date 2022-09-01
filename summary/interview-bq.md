1. Tell me about **yourself**, whatever's not on your resume.

My name is Lan Zhang. I’m a fourth-year Ph.D. candidate at Penn state university. My works focus on **AI for cybersecurity**. More specifically about attacks and defense on malware and microcontrollers. Before that, I receive my bachelor degree and master degree in software engineering at bjtu and tsinghua university in china. working on differential privacy. 

2. Tell me a time when you had to learn something **challenging**, and how did you go about learning it.

2. Tell me a time you stepped out of your comfort zone.

2. Tell me a time when you had to dive deep/go in depth into something.

2. **Learn and Be Curious**: Leaders are never done learning and always seek to improve themselves. They are curious about new possibilities and act to explore them.

my current firmware emulation project is quite challenging.

S: It is challenging because it is a brand new area to me. before this, I know nothing about vulnerabilities in MCUs.  

T: The goal of this projects is to extract knowledge from the MCU manuals, and construct models to emulate the logic of the hardware and  dynamically update the registers of the peripherals, so the models could give correct response to the fimware. I'm more familar with information retrieval but I don't know how to combine the symbolic execution with concrete execution. so that when the firmware access to the mmio address, it can get real-time reponse based on the knowledge we extracted from MCU manuals.

A: I first googled a lot of papers related to firmware emulation. When I came up with some ideas, I would discuss with my collaborators to make sure it is feasible and we are on the same page. We use NLP tools to retrieve the relation and logics of registers and fields, and I learnt lots of new tools by myself such as S2E, Qemu, and Pandas for symbolic execution

R: Finally, I designed and implement the emulation model and worte a manuscript which has been accepted by ccs 2022. through this process, I not only learnt new techniques but the ability to do research on something totally new. it is so important to be curious and keep learning. 

3. Tell me a time where you got **criticism** and how did you handle it?

3. the biggest **mistake** you made and what did you learn from it? (earn trust, customer obsession)

S: I remember I was collaborating with two researchers from different area and different time zone. I updated the progress with my advisor every week. but sometimes didnot keep other collaborators up-to-date. 

T: I met issues to implement the taint analysis with avatar2. I had sent messages to the authors on github and got no response. My advisor said I should have shared the issue with other collaborator to see if they got ideas to resolve that. 

A:  it turns out one of my collaborator has connection with the author, and he forwart my email to them and they help me to fix the bug.

R: So through this process, I relized it is important to communicate with my collaborator. I summarize our weekly meeting, update the progress with all members every week. When I came up with some ideas, I would discuss with my collaborators to make sure it is feasible and we are on the same page.

4. Tell me about your **career goals**.

4. Why are you applying for this position?

4. Why do you want this job? 		 	 	 					

4. Why do you want to work here?							

4. What are you passionate about? 

build some interesting project that influence an area. My project can make life easier and inspire more people. It's not just one manuscript/ research based on lots of hypothsis but something really useful in our daily life.

5. Which of the 14 Leadership Principles do you resonate the most with and why?

https://www.xiakexing.me/forum.php?mod=viewthread&tid=3600&highlight=amazon%2Bintern%2B%E9%9D%A2%E8%AF%95

6. **Ownership**: Leaders are owners. They think long term and don’t sacrifice long-term value for short-term results. They act on behalf of the entire company, beyond just their own team. They never say “that’s not my job."

6. tell a time do something out of resposibility

6. tell a time help peers

6. **Invent and Simplify**: Leaders expect and require innovation and invention from their teams and always find ways to simplify. They are externally aware, look for new ideas from everywhere, and are not limited by “not invented here." As we do new things, we accept that we may be misunderstood for long periods of time.

6. Tell me about the most innovative thing you did.

6. **Are Right, A Lot**: Leaders are right a lot. They have strong judgment and good instincts. They seek diverse perspectives and work to disconfirm their beliefs.

6. **Insist on the Highest Standards**: Leaders have relentlessly high standards — many people may think these standards are unreasonably high. Leaders are continually raising the bar and drive their teams to deliver high quality products, services, and processes. Leaders ensure that defects do not get sent down the line and that problems are fixed so they stay fixed.

6. **Think Big**: Thinking small is a self-fulfilling prophecy. Leaders create and communicate a bold direction that inspires results. They think differently and look around corners for ways to serve customers.

S: I remember one project I did when I was undergrats. I collaratate with two classmates to build a a wearable device (baseball hat) integrating micro camera and Raspberry Pi to navigate the blind and identify and recongize people on their way. 

T: one of them work on install a microcamera on the raspberry Pi and sent photos to the phone. My job was to get the photo and detect characteristics of pedestrians (e.g. age, gender) using facial detection. Another friend implement an app to provide voice navigation to destination. But he had to quit the project for personal reason. It was close to the deadline. They suggested to remove that function. but I think then our orignal goal cannot be achieved. 

A: So I took the responsibility to implement that function. I first checked the progress of my friend. Read his code and mark the code snippet that I didn't understand. and ask him what was left. and worked for days to implement that function.

R: I learnt a lot from this experience. 

7. What **programming languages** do you know and do you want to learn?

CPP & Python

rust: Rust provides the feature of threads without data races because of the ownership system. Ownership system transmits only the owners of different objects to different threads, and two threads can never own the same variable with write access.

Rust guaranteed the memory safety by using the concept of ownership. 

8. do sth. without telling advisor



9. Earn Trust: Leaders listen attentively, speak candidly, and treat others respectfully. They are vocally self-critical, even when doing so is awkward or embarrassing. Leaders do not believe their or their team’s body odor smells of perfume. They benchmark themselves and their teams against the best.

9. 一个问了我关于在团队中如何应对different opinions，如何solve conflicts



10. Bias for Action: Speed matters in business. Many decisions and actions are reversible and do not need extensive study. We value **calculated risk** taking. 

10. tell a time miss the **deadline**

The biggest mistake I’ve made happened when I led the smartloganalyzer project for the first time. The original schedule is week, but I suddenly received a message from my manager says that he will show a smartloganalyzer demo to one customer after two days. And at that time I was working on building the alerting system, that will be an important part of the demo. But I paid too much attention on details, I want to make everything perfect. I didn’t notice that I don’t have enough time to finish all the details. Last day before the demo day, my manager pointed that out. I apologized to him and then we started to figure out if there is a way to keep the demo the same as what we want it to be, but sacrificing some backend performance that customer won’t notice, cause it is just a demo. After the demo, I can rewrite the code to meet my requirements. Fortunately, the demonstration was not affected in the end. But from this mistake, I learnt that details are definitely important, but I also need to pay attention to the whole schedule, I need to always keep good communication with my teammates when I have my plan. I need to make sure that my schedule won’t affect other’s schedule.

I will discuss with my colleagues, trying to figure out a way that can improve the efficiency and If necessary, I will use my private time to keep working on the task. After all, finishing the task with high quality as soon as possible is what we want. I’ll never sacrifice the customer experience or the quality of the product because of that. Customer experience is always the most important. We must make sure that the product we are gonna deliver is qualified. We can sacrifice our own time to try to finish the tasks. If we still can not finish the tasks, we will communicate with customers and related people, to tell them why and earn their trust. At the same time, we will try our best to finish the tasks as soon as possible.

7. Hire and Develop the Best: Leaders raise the performance bar with every hire and promotion. They recognize exceptional talent, and willingly move them throughout the organization. Leaders develop leaders and take seriously their role in **coaching others**. We work on behalf of our people to invent mechanisms for development like Career Choice.

9. Frugality: Accomplish more with less. Constraints breed resourcefulness, self-sufficiency, and invention. There are no extra points for growing headcount, budget size, or fixed expense.

11. Dive Deep: Leaders operate at all levels, stay connected to the details, audit frequently, and are skeptical when metrics and anecdote differ. No task is beneath them.

12.  Have Backbone; Disagree and Commit: Leaders are obligated to respectfully challenge decisions when they disagree, even when doing so is uncomfortable or exhausting. Leaders have conviction and are tenacious. They do not compromise for the sake of social cohesion. Once a decision is determined, they commit wholly.

13. Deliver Results: Leaders focus on the key inputs for their business and deliver them with the right quality and in a timely fashion. Despite setbacks, they rise to the occasion and never settle.

14. Strive to be Earth's Best Employer: Leaders work every day to create a safer, more productive, higher performing, more diverse, and more just work environment. They lead with empathy, have fun at work, and make it easy for others to have fun. Leaders ask themselves: Are my fellow employees growing? Are they empowered? Are they ready for what's next? Leaders have a vision for and commitment to their employees' personal success, whether that be at Amazon or elsewhere.

15. Success and Scale Bring Broad Responsibility: We started in a garage, but we're not there anymore. We are big, we impact the world, and we are far from perfect. We must be humble and thoughtful about even the secondary effects of our actions. Our local communities, planet, and future generations need us to be better every day. We must begin each day with a determination to make better, do better, and be better for our customers, our employees, our partners, and the world at large. And we must end every day knowing we can do even more tomorrow. Leaders create more than they consume and always leave things better than how they found them.



- ***Why [Amazon](http://www.amazon.com/b?_encoding=UTF8&tag=1p3a-guanlian-20&linkCode=ur2&linkId=89c11e2c5b86155c5422f19cca1e9880&camp=1789&creative=9325&node=5)?***

Because I know Amazon is a top internet retailing company with a strong focus on customer experience. And there are a lot of talented people in amazon creating amazing products to make people’s life easier. They are always showing strong ownership to their projects and they always want to make things perfect. Those spirits do touch my heart. I remember when I just started to lead smart log analyzer project, everything is new to me. And I’m so passionate about creating great services for customers to save their precious time and money. They could have people hired to sit there watching the visuals we provide, and trying to do treat hunting, to see if there are malicious events among them. But we want it to be more convenient. We want our system to take care of all the stuff automatically. It will detect the malicious stuff, evaluate them, report them and provide suggestions and solve them automatically. The customer only needs to do clicks on the website to make simple decisions based on the suggestions system provide and they can focus more on their own things. That is really similar with Quilt. Quilt also does a great job to help customers focus on their codes. It will take care of patching automatically for hosts. That’s really amazing for customer. So, we have similar spirits. That’s one big reason why I want to join Amazon.
Secondly, the growth of amazon is so impressive, it is not only an online retail shop, it also has a wide range of products like Alexa, [kindle](http://amzn.to/2PcJxHB), fire tablet and TV, Amazon web service, etc. There are so many fantastic technologies and products here. I will never feel boring if I am in amazon. And I’ll be excited about all the amazing things around me everyday. I can learn a lot of new technologies here. Beside that, I can also learn to work with solutions with full-stack point of view, by engaging requirements, front-end, back-end, storage and all the other stuff. I can understand the problems and solutions thoroughly.

-----

what's your favorite leadership principle

intern的参与度能有多高 然后小哥给我讲了好多intern日常

