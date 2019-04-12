using UnityEngine;
using System.Collections;

public class NPCTankController : AdvancedFSM 
{
    public GameObject Bullet;
    private float health;
    public float Health
    {
        get { return health; }
    }
    private const int HEAL_BUFF = 10;
    private const int DAM_THRESH = 60;
    private bool isHealing;
    public bool IsHealing
    {
        get { return isHealing; }
    }
    private bool isInvincible;
    private float probOfBoredom;
    private float elapsedBoredTime;
    private const float MAX_BORED_TIME = 5f;
    private MeshRenderer mRend;

    //Initialize the Finite state machine for the NPC tank
    protected override void Initialize()
    {
        health = 100f;
        isHealing = false;
        isInvincible = false;

        elapsedTime = 0.0f;
        shootRate = 2.0f;
        probOfBoredom = 0.1f;
        elapsedBoredTime = 0f;

        //Get the target enemy(Player)
        GameObject objPlayer = GameObject.FindGameObjectWithTag("Player");
        playerTransform = objPlayer.transform;
        //Locate heal station
        GameObject objHealing = GameObject.FindGameObjectWithTag("Heal");
        healingTransform = objHealing.transform;

        mRend = GetComponent<MeshRenderer>();

        if (!playerTransform)
            print("Player doesn't exist.. Please add one with Tag named 'Player'");

        //Get the turret of the tank
        turret = gameObject.transform.GetChild(0).transform;
        bulletSpawnPoint = turret.GetChild(0).transform;

        //Start Doing the Finite State Machine
        ConstructFSM();
    }

    //Update each frame
    protected override void FSMUpdate()
    {
        //Check for health
        elapsedTime += Time.deltaTime;

        if (prevStateID != CurrentStateID)
            SwapColor();
    }

    protected override void FSMFixedUpdate()
    {
        CurrentState.Reason(playerTransform, transform);
        CurrentState.Act(playerTransform, transform);
    }

    public void SetTransition(Transition t) 
    { 
        PerformTransition(t); 
    }

    private void ConstructFSM()
    {
        //Get the list of points
        pointList = GameObject.FindGameObjectsWithTag("WandarPoint");

        Transform[] waypoints = new Transform[pointList.Length];
        int i = 0;
        foreach(GameObject obj in pointList)
        {
            waypoints[i] = obj.transform;
            i++;
        }

        PatrolState patrol = new PatrolState(waypoints, this);
        patrol.AddTransition(Transition.SawPlayer, FSMStateID.Chasing);
        patrol.AddTransition(Transition.LowHealth, FSMStateID.Healing);
        patrol.AddTransition(Transition.NoHealth, FSMStateID.Dead);
        patrol.AddTransition(Transition.HasBoredom, FSMStateID.Bored);

        ChaseState chase = new ChaseState(waypoints, this);
        chase.AddTransition(Transition.LostPlayer, FSMStateID.Patrolling);
        chase.AddTransition(Transition.ReachPlayer, FSMStateID.Attacking);
        chase.AddTransition(Transition.LowHealth, FSMStateID.Healing);
        chase.AddTransition(Transition.NoHealth, FSMStateID.Dead);

        AttackState attack = new AttackState(waypoints, this);
        attack.AddTransition(Transition.LostPlayer, FSMStateID.Patrolling);
        attack.AddTransition(Transition.SawPlayer, FSMStateID.Chasing);
        attack.AddTransition(Transition.LowHealth, FSMStateID.Healing);
        attack.AddTransition(Transition.NoHealth, FSMStateID.Dead);

        DeadState dead = new DeadState();
        dead.AddTransition(Transition.NoHealth, FSMStateID.Dead);

        HealState heal = new HealState(waypoints, this);
        heal.AddTransition(Transition.SawPlayer, FSMStateID.Chasing);
        heal.AddTransition(Transition.LostPlayer, FSMStateID.Patrolling);
        heal.AddTransition(Transition.NoHealth, FSMStateID.Dead);

        BoredState bored = new BoredState(waypoints, this);
        bored.AddTransition(Transition.SawPlayer, FSMStateID.Chasing);
        bored.AddTransition(Transition.LostPlayer, FSMStateID.Patrolling);
        bored.AddTransition(Transition.LowHealth, FSMStateID.Healing);
        bored.AddTransition(Transition.NoHealth, FSMStateID.Dead);

        AddFSMState(patrol);
        AddFSMState(chase);
        AddFSMState(attack);
        AddFSMState(dead);
        AddFSMState(heal);
        AddFSMState(bored);
    }

    /// <summary>
    /// Check the collision with the bullet
    /// </summary>
    /// <param name="collision"></param>
    void OnCollisionEnter(Collision collision)
    {
        //Reduce health
        if (collision.gameObject.tag == "Bullet" && isInvincible == false)
        {
            health -= 50f;
            if (health <= DAM_THRESH && CurrentStateID != FSMStateID.Healing)
            {
                Debug.Log("Switch to Heal State");
                SetTransition(Transition.LowHealth);
            }
            else if (health <= 0f)
            {
                Debug.Log("Switch to Dead State");
                SetTransition(Transition.NoHealth);
                Explode();
            }
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.CompareTag("Heal"))
        {
            isInvincible = true;
            if (CurrentStateID == FSMStateID.Healing)
            {
                isHealing = true;
            }
        }
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.CompareTag("Heal"))
            isInvincible = false;
    }

    protected void Explode()
    {
        float rndX = Random.Range(10.0f, 30.0f);
        float rndZ = Random.Range(10.0f, 30.0f);
        for (int i = 0; i < 3; i++)
        {
            GetComponent<Rigidbody>().AddExplosionForce(10000.0f, transform.position - new Vector3(rndX, 10.0f, rndZ), 40.0f, 10.0f);
            GetComponent<Rigidbody>().velocity = transform.TransformDirection(new Vector3(rndX, 20.0f, rndZ));
        }

        Destroy(gameObject, 1.5f);
    }

    /// <summary>
    /// Shoot the bullet from the turret
    /// </summary>
    public void ShootBullet()
    {
        if (elapsedTime >= shootRate)
        {
            Instantiate(Bullet, bulletSpawnPoint.position, bulletSpawnPoint.rotation);
            elapsedTime = 0.0f;
        }
    }

    public void Heal()
    {
        Debug.Log("Healing: " + health);
        health += HEAL_BUFF * Time.deltaTime;
        if (health >= 100.0f)
        {
            health = 100.0f;
            isHealing = false;
        }
    }

    public void TryStartBoredom()
    {
        float rand = Random.Range(0f, 100f);
        Debug.Log("Rand: " + rand);
        if (rand <= probOfBoredom)
        {
            SetTransition(Transition.HasBoredom);
            elapsedBoredTime = 0f;
        }
    }

    public void TryEndBoredom()
    {
        elapsedBoredTime += Time.deltaTime;
        Debug.Log("Elapsed Bored Time: " + elapsedBoredTime);
        if (elapsedBoredTime >= MAX_BORED_TIME)
            SetTransition(Transition.LostPlayer);
    }

    public void SwapColor()
    {
        CurrentState.ApplyColor(mRend.material);
        prevStateID = CurrentStateID;
    }
}