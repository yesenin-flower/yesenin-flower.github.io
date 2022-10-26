> Tell me about **yourself**, whatever's not on your resume.

My name is Lan Zhang. I’m a fourth-year Ph.D. candidate at Penn state university. My works focus on **AI for cybersecurity**. More specifically it's about using graph based models and NLP analysis to support malware analysis and firmware emulation. Before that, I receive my bachelor degree and master degree in software engineering at bjtu and tsinghua university in china. 

> Tell me a time when you had to learn something **challenging**, and how did you go about learning it.
>
> Tell me a time you stepped out of your comfort zone.
>
> Tell me a time when you had to dive deep/go in depth into something.
>
> **Learn and Be Curious**: Leaders are never done learning and always seek to improve themselves. They are curious about new possibilities and act to explore them.

my current firmware emulation project is quite challenging.

S: It is challenging because it is a **brand new** area to me. before this, I know nothing about vulnerabilities in MCUs.  

T: The goal of this projects is to rehost the IoT firmware on a PC, so we can do security analysis without real MCUs. our idea is to extract knowledge from the MCU manuals, and construct a real-time model to emulate the logic of the hardware, so the models could give correct response to the fimware. I joined this project because i'm familar with information retreveal. but I'm not familar with firmware emulation.

A: I first googled a lot of papers related to this topic. When I came up with some ideas, I would discuss this with my collaborators to make sure it is feasible. I learnt lots of new tools by myself such as S2E, Qemu, and Pandas // to combine the symbolic execution with concrete execution. so that when the firmware access to the mmio address of MCUs, it can reach to the NLP engine and get real-time reponse based on the knowledge we extracted.

R: Finally, I designed and implement the emulation model and worte a manuscript which has been accepted by ccs 2022. I learn a lot from this project. I not only learnt new techniques but the ability to do research on something totally new. it is so important to be curious and keep learning. 

> Tell me a time where you got **criticism** and how did you handle it?
>
> the biggest **mistake** you made and what did you learn from it?
>
> **do sth. without telling advisor**
>
> **tell a time miss the deadline**
>
> Tell the story of the last time you had to apologize to someone.

S: firmware emulation; one sub-task, the goal is to implement the taint analysis with avatar2 within one week. it's a new semantic analysis tool released on github. at first we think it can be done within one week, because they provide a plugin that support the function. but it turns out the plugin is outdated. So I first raise issues on github and email the corresponding authors of the paper. But I got no response after one day. 

T: And I did not update this progress with collaborators imedieatly. I thought maybe I could implement the plugin by myself. I thought it is just a small issue, but the dependencies are way too complicated, one code snippet, lots of packages need to be updated, that I don’t have enough time to reimplement it within one week. Two days before the deadline, my advisor checked in, details and said i should share the issue with other collaborators to see if they got ideas to resolve that. 

A:  it turns out one of my collaborator has connection with the author, and he forwart my email to them and help me to fix the plugin.

R:  But from this mistake, I relized it is important to communicate with my collaborator. I summarize our weekly meeting, update the progress with all members to make sure we are on the same page. When I came up with some ideas, I would discuss with my collaborators to make sure it is feasible.

> Tell me about your **career goals**.
>
> Why are you applying for this position?
>
> Why do you want this job? 		 	 	 					
>
> **Why do you want to work here?	**						
>
> What are you passionate about? 

My career goal is to build some meaningful, impactful projects that can make people’s life easier. It's not just one manuscript/ research based on lots of hypotheses but something really useful in our daily life. Amazon is a top internet retailing company. And there are a lot of talents creating amazing products, like Alexa, kindle, and AWS, to save customers' precious time and money.  we have similar goal and I can learn a lot of new technologies here. That’s one big reason why I want to join Amazon. 

https://www.xiakexing.me/forum.php?mod=viewthread&tid=3600&highlight=amazon%2Bintern%2B%E9%9D%A2%E8%AF%95

> Customer Obsession
>
> Who was your most difficult customer?
> Give me an example of a time when you did not meet a client’s expectation. What happened, and how did you attempt to rectify the situation?
> When you’re working with a large number of customers, it’s tricky to deliver excellent service to them all. How do you go about prioritizing your customers’ needs?
>
> Bias for Action: Speed matters in business. Many decisions and actions are reversible and do not need extensive study. We value **calculated risk** taking. 

When I was interned at Baidu, I was working with several projects. One is to relation extraction from unstructured corpus. Cause I have no idea how to knowlege graph and relation extraction. I first googled a lot of papers and learnt the basic concepts.  Based on that, I started to discuss with my project manager to figure out our final goal. though my manager is familiar with the application of knowledge graph but she's not professional developer. So I explained the challenges to extract those information from our corpus with lots of examples. like sentences in our corpus are cralwed online, it's too coarse. some of them are not even  an actual sentences, but just words generated by robots. after several round, we made it clear that they just need to update the existing knowledge base. It's okay to have low recall rate. but they care about accuracy and false positive. So I decide to combine two methods toghter. first use machine learning to extract candidates SPO tripes and then calculate confidential score based on the several rules. so they could choose top candidates to update the knowlege base. So, finally, after the delivery, I get positive feedbacks from PM. 

After that, I started to work with customers to figure out what kind of problems that customers concerned the most. we decide to work on family relationship first. then I broke down the projects into milestones and small task. cleaning data from different sources, feature selection and combine them together, training different models.  With the first glance, you can hardly know what to do first. So to simplify it, I sort the tasks based on urgency and importance and build a timeline. With the timeline, we can schedule the tasks more easily.

>  **Ownership**: Leaders are owners. They think long term and don’t sacrifice long-term value for short-term results. They act on behalf of the entire company, beyond just their own team. They never say “that’s not my job."
>
> **tell a time do something out of resposibility**
>
> tell a time help peers
>
> **Invent and Simplify**: Leaders expect and require innovation and invention from their teams and always find ways to simplify. They are externally aware, look for new ideas from everywhere, and are not limited by “not invented here." As we do new things, we accept that we may be misunderstood for long periods of time. 
>
> Tell me about the most innovative thing you did.
>
> **Are Right, A Lot**: Leaders are right a lot. They have strong judgment and good instincts. They seek diverse perspectives and work to disconfirm their beliefs.
>
> **Insist on the Highest Standards**: Leaders have relentlessly high standards — many people may think these standards are unreasonably high. Leaders are continually raising the bar and drive their teams to deliver high quality products, services, and processes. Leaders ensure that defects do not get sent down the line and that problems are fixed so they stay fixed.
>
> **Think Big**: Thinking small is a self-fulfilling prophecy. Leaders create and communicate a bold direction that inspires results. They think differently and look around corners for ways to serve customers.
>
> Earn Trust: Leaders listen attentively, speak candidly, and treat others respectfully. They are vocally self-critical, even when doing so is awkward or embarrassing. Leaders do not believe their or their team’s body odor smells of perfume. They benchmark themselves and their teams against the best.
>
> 一个问了我关于在团队中如何应对different opinions，如何solve conflicts
>
> Hire and Develop the Best: Leaders raise the performance bar with every hire and promotion. They recognize exceptional talent, and willingly move them throughout the organization. Leaders develop leaders and take seriously their role in **coaching others**. We work on behalf of our people to invent mechanisms for development like Career Choice.
>
> Have Backbone; Disagree and Commit: Leaders are obligated to respectfully challenge decisions when they disagree, even when doing so is uncomfortable or exhausting. Leaders have conviction and are tenacious. They do not compromise for the sake of social cohesion. Once a decision is determined, they commit wholly.

S: I remember one project I did when I was undergrats. I collaratated with two classmates to build a a wearable device (baseball hat) integrating micro camera and Raspberry Pi to navigate the blind and help them to identify and recongize pedestrians in front of them. 

T: one of them work on installing a microcamera on the raspberry Pi and sent photos to the phone. My job was to get the photo and detect pedestrians. Another friend implement an app to provide voice navigation. But he had to quit the project for personal reason. It was close to the deadline. They suggested to remove that function. but I think then our orignal goal cannot be achieved. 

A: So I took the responsibility to implement that function.  /trying to figure out a way to help me. I first checked the progress of my friend. Read his code and mark the code snippet that I didn't understand. and ask him what was left. I use my private time to keep working on the task.  Google and ask other friends who is familiar with android development to solve the issue. 

A2:  I first checked the progress of my friend. Read his code and mark the code snippet that I didn't understand. and ask him what was left. then I invited another friend to join the team. at first, he told me he was able to do it. But I found that he gets lost about what we are doing and what he is going to do. So, I told him that it is not as complex as what he is thinking about. I break down the projects into milestones and small task. and explained to him what we need to do next. After he is getting familar with the whole project, I started to assign him the specific task. And he is doing pretty well. So when someone comes to a new environment, getting lost is quite normal. We need to have patience to make him get comfortable of the whole environment. 

R: I learnt a lot from this experience. that in a team, the most important thing is to reach the goal. finishing the task with high quality as soon as possible is what we want. I’ll never sacrifice the customer experience or the quality of the product because of that. do give up before you tried. you spend enough time, collaborate actively with others, you may acheive the goal. 

> What **programming languages** do you know and do you want to learn?

CPP & Python

rust: Rust provides the feature of threads without data races because of the ownership system. Ownership system transmits only the owners of different objects to different threads, and two threads can never own the same variable with write access.

Rust guaranteed the memory safety by using the concept of ownership. 

> Who was your most difficult customer?
> Give me an example of a time when you did not meet a client’s expectation. What happened, and how did you attempt to rectify the situation?
> When you’re working with a large number of customers, it’s tricky to deliver excellent service to them all. How do you go about prioritizing your customers’ needs?
> Tell the story of the last time you had to apologize to someone.



7. Frugality: Accomplish more with less. Constraints breed resourcefulness, self-sufficiency, and invention. There are no extra points for growing headcount, budget size, or fixed expense.



1. Dive Deep: Leaders operate at all levels, stay connected to the details, audit frequently, and are skeptical when metrics and anecdote differ. No task is beneath them.
2. Deliver Results: Leaders focus on the key inputs for their business and deliver them with the right quality and in a timely fashion. Despite setbacks, they rise to the occasion and never settle.
3. Strive to be Earth's Best Employer: Leaders work every day to create a safer, more productive, higher performing, more diverse, and more just work environment. They lead with empathy, have fun at work, and make it easy for others to have fun. Leaders ask themselves: Are my fellow employees growing? Are they empowered? Are they ready for what's next? Leaders have a vision for and commitment to their employees' personal success, whether that be at Amazon or elsewhere.
4. Success and Scale Bring Broad Responsibility: We started in a garage, but we're not there anymore. We are big, we impact the world, and we are far from perfect. We must be humble and thoughtful about even the secondary effects of our actions. Our local communities, planet, and future generations need us to be better every day. We must begin each day with a determination to make better, do better, and be better for our customers, our employees, our partners, and the world at large. And we must end every day knowing we can do even more tomorrow. Leaders create more than they consume and always leave things better than how they found them.

-----

what's your favorite leadership principle

intern的参与度能有多高 然后小哥给我讲了好多intern日常

